#include <math.h>

#include <glwidget.h>
#include <QString>

GLWidget::GLWidget(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)

{
    //std::cout<<"GLWidget::GLWidget"<<std::endl;
    setFocusPolicy( Qt::StrongFocus );

    cameraActual = true;
    esc = new Escena(this->size().width(), this->size().height());

    xRot = 0;
    yRot = 0;
    zRot = 0;

    a = 20.0;
    h = 20.0;
    p = 20.0;

    clearColor = Qt::black;
    qtGreen = QColor::fromCmykF(0.40, 0.0, 1.0, 0.0);
    qtPurple = QColor::fromCmykF(0.39, 0.39, 0.0, 0.0);

    tipoShading = "Flat";
    esc->teTextura = false;
    program = 0;
    moviment = false;
}


GLWidget::~GLWidget()
{
    makeCurrent();
    delete esc;
}


// Create a GLSL program object from vertex and fragment shader files
void
GLWidget::InitShaderGPU()
{
    vshaderFlatGouraud = new QGLShader(QGLShader::Vertex, this);
    fshaderFlatGouraud = new QGLShader(QGLShader::Fragment, this);
    vshaderPhong = new QGLShader(QGLShader::Vertex, this);
    fshaderPhong = new QGLShader(QGLShader::Fragment, this);
    vshaderToon = new QGLShader(QGLShader::Vertex, this);
    fshaderToon = new QGLShader(QGLShader::Fragment, this);

    vshaderFlatGouraud->compileSourceFile("://vshaderFlatGouraud.glsl");
    fshaderFlatGouraud->compileSourceFile("://fshaderFlatGouraud.glsl");
    vshaderPhong->compileSourceFile("://vshaderPhong.glsl");
    fshaderPhong->compileSourceFile("://fshaderPhong.glsl");
    vshaderToon->compileSourceFile("://vshaderToon.glsl");
    fshaderToon->compileSourceFile("://fshaderToon.glsl");

    program = new QGLShaderProgram(this);

    if(tipoShading == "Flat" || tipoShading == "Gouraud"){
        program->addShader(vshaderFlatGouraud);
        program->addShader(fshaderFlatGouraud);
    }else if(tipoShading == "Phong"){
        program->addShader(vshaderPhong);
        program->addShader(fshaderPhong);
    }else{
        program->addShader(vshaderToon);
        program->addShader(fshaderToon);
    }

    program->bindAttributeLocation("vPosition", PROGRAM_VERTEX_ATTRIBUTE);
    program->bindAttributeLocation("vColor", PROGRAM_COLOR_ATTRIBUTE);


    // muntatge del shader en el pipeline gràfic per a ser usat
    program->link();

    // unió del shader al pipeline gràfic
    program->bind();
}



QSize GLWidget::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize GLWidget::sizeHint() const

{
    return QSize(400, 400);
}


static void qNormalizeAngle(int &angle)
{
    while (angle < 0)
        angle += 360;
    while (angle > 360)
        angle -= 360;
}


void GLWidget::setXRotation(int angle)
{
    Camera camActual;
    if(cameraActual) camActual = esc->camGeneral;
    else camActual = esc->camFirstP;
    qNormalizeAngle(angle);
    xRot += camActual.vs.angx;
    if (angle != xRot) {
        xRot = angle;
        update();
    }
}


void GLWidget::setYRotation(int angle)
{
    Camera camActual;
    if(cameraActual) camActual = esc->camGeneral;
    else camActual = esc->camFirstP;
    qNormalizeAngle(angle);
    yRot += camActual.vs.angy;
    if (angle != yRot) {
        yRot = angle;
        update();
    }

}

void GLWidget::setZRotation(int angle)
{
    Camera camActual;
    if(cameraActual) camActual = esc->camGeneral;
    else camActual = esc->camFirstP;
    qNormalizeAngle(angle);
    yRot += camActual.vs.angy;
    if (angle != yRot) {
        yRot = angle;
        update();
    }
}

void GLWidget::initializeGL()
{
    //std::cout<<"GLWidget::initializeGL"<<std::endl;
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    InitShaderGPU();
    esc->pr = program;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if(cameraActual==true){
        esc->camGeneral.toGPU(program);
    }
    esc->setAmbientToGPU(program);
    esc->conjuntLlums->toGPU(program);
}

void GLWidget::paintGL()
{
   glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
   esc->draw(cameraActual);
}


void GLWidget::resizeGL(int width, int height)
{
    int side = qMin(width, height);
    glViewport((width - side) / 2, (height - side) / 2, side, side);

    if(cameraActual==true){
        esc->camGeneral.setViewport(0, 0, width, height);
    }
}


void GLWidget::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(cameraActual == false)return;//solo funciona con camGeneral

    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();


    if (event->buttons() & Qt::LeftButton) {
        if(lastPos.y()!= event->y() && lastPos.x()!= event->x()) {//no utilizado por consideraciones de diseño
            setYRotation(xRot + 1 * dy);
            setXRotation(yRot + 1 * dx);
        }
    }

    lastPos = event->pos();
    esc->setAnglesCamera(cameraActual, xRot, yRot, zRot);
}


void GLWidget::changeShader(QString Shading, bool Text){
    QString tipoShadingOld = tipoShading;
    esc->teTextura = Text;
    if(tipoShading != Shading){
        if(((tipoShading == "Flat" || tipoShading == "Gouraud") && (Shading != "Flat" && Shading != "Gouraud")) ||
              ((tipoShading != "Flat" && tipoShading != "Gouraud"))  ){
            tipoShading = Shading;
            // eliminem els shaders i assignem el nou
            program->removeAllShaders();
            if(this->tipoShading == "Flat" || this->tipoShading =="Gouraud"){
                program->addShader(vshaderFlatGouraud);
                program->addShader(fshaderFlatGouraud);
            }else if(this->tipoShading == "Phong"){
                program->addShader(vshaderPhong);
                program->addShader(fshaderPhong);
            }else{
                program->addShader(vshaderToon);
                program->addShader(fshaderToon);
            }
            program->link();
            program->bind();
        }
        if((tipoShadingOld == "Flat" && Shading != "Flat") || (tipoShadingOld != "Flat" && Shading == "Flat")){
            tipoShading = Shading;
            newSalaBillar();
        }else{
            tipoShading = Shading;
        }
    }
}


void GLWidget::keyPressEvent(QKeyEvent *event)
{
    mat4 m;
    double angx;
    cb = esc->bolaBlanca->calculCapsa3D();
    ctrB.x = cb.pmin.x + cb.a/2.0;
    ctrB.y = cb.pmin.y + cb.h/2.0;
    ctrB.z = cb.pmin.z + cb.p/2.0;

    if (esc->bolaBlanca!=NULL && esc->plaBase!=NULL && esc->conjuntBoles!=NULL){
        esc->computeCollisions(cb, cT, ctrB, listaCapsasConjuntBoles, event);
    }
   switch ( event->key() )
   {
   case Qt::Key_1:
       if (event->modifiers() & Qt::AltModifier){
         changeShader("Flat", true);
         break;
       }
       changeShader("Flat", false);
       break;

   case Qt::Key_2:
       if (event->modifiers() & Qt::AltModifier){
         changeShader("Gouraud", true);
         break;
       }
       changeShader("Gouraud", false);
       break;

   case Qt::Key_3:
       if (event->modifiers() & Qt::AltModifier){
         changeShader("Phong", true);
         break;
       }
       changeShader("Phong", false);
       break;

   case Qt::Key_4:
       if (event->modifiers() & Qt::AltModifier){
         changeShader("Toon", true);
         break;
       }
       changeShader("Toon", false);
       break;

   case Qt::Key_Up:
       if (event->modifiers() & Qt::AltModifier){
            Pan(0, 0.01);
            break;
       }
       m = Translate(0.0,  0.0, esc->dzN) * Translate(ctrB.x,  ctrB.y, ctrB.z) * RotateX((esc->dzN*180.0)/(0.0307474*M_PI)) * Translate(-ctrB.x,  -ctrB.y, -ctrB.z );
       for(int i = 0; i<esc->bolaBlanca->Index; i++){
         vec4 kk  = (Translate(ctrB.x,  ctrB.y, ctrB.z) * RotateX((esc->dzN*180.0)/(0.0307474*M_PI)) * Translate(-ctrB.x,  -ctrB.y, -ctrB.z ) * vec4(esc->bolaBlanca->normal[i],0));
         esc->bolaBlanca->normal[i] = vec3(kk.x, kk.y, kk.z);
       }
       break;
   case Qt::Key_Down:
        if (event->modifiers() & Qt::AltModifier){
          Pan(0, -0.01);
          break;
        }
        m = Translate(0.0,  0.0, esc->dzP) * Translate(ctrB.x,  ctrB.y, ctrB.z) * RotateX((esc->dzP*180.0)/(0.0307474*M_PI)) * Translate(-ctrB.x,  -ctrB.y, -ctrB.z );
        for(int i = 0; i<esc->bolaBlanca->Index; i++){
          vec4 kk  = (Translate(ctrB.x,  ctrB.y, ctrB.z) * RotateX((esc->dzP*180.0)/(0.0307474*M_PI)) * Translate(-ctrB.x,  -ctrB.y, -ctrB.z ) * vec4(esc->bolaBlanca->normal[i],0));
          esc->bolaBlanca->normal[i] = vec3(kk.x, kk.y, kk.z);
        }
        break;
   case Qt::Key_Left:
       if (event->modifiers() & Qt::AltModifier){
          Pan(-0.01, 0);
          break;
       }
       m = Translate(esc->dxN,  0.0, 0.0) * Translate(ctrB.x,  ctrB.y, ctrB.z) * RotateZ(-(esc->dxN*180.0)/(0.0307474*M_PI)) * Translate(-ctrB.x,  -ctrB.y, -ctrB.z );
       for(int i = 0; i<esc->bolaBlanca->Index; i++){
         vec4 kk  = (Translate(ctrB.x,  ctrB.y, ctrB.z) * RotateZ(-(esc->dxN*180.0)/(0.0307474*M_PI)) * Translate(-ctrB.x,  -ctrB.y, -ctrB.z ) * vec4(esc->bolaBlanca->normal[i],0));
         esc->bolaBlanca->normal[i] = vec3(kk.x, kk.y, kk.z);
       }
       break;
   case Qt::Key_Right:
      if (event->modifiers() & Qt::AltModifier){
          Pan(0.01, 0);
          break;
       }
       m = Translate(esc->dxP,  0.0, 0.0) * Translate(ctrB.x,  ctrB.y, ctrB.z) * RotateZ(-(esc->dxP*180.0)/(0.0307474*M_PI)) * Translate(-ctrB.x,  -ctrB.y, -ctrB.z );
       for(int i = 0; i<esc->bolaBlanca->Index; i++){
         vec4 kk  = (Translate(ctrB.x,  ctrB.y, ctrB.z) * RotateZ(-(esc->dxP*180.0)/(0.0307474*M_PI)) * Translate(-ctrB.x,  -ctrB.y, -ctrB.z ) * vec4(esc->bolaBlanca->normal[i],0));
         esc->bolaBlanca->normal[i] = vec3(kk.x, kk.y, kk.z);
       }
       break;
   case Qt::Key_Plus:
       Zoom(-0.05);
       break;
   case Qt::Key_Minus:
       Zoom(0.05);
       break;
   }

   if (esc->bolaBlanca!=NULL){
      esc->bolaBlanca->aplicaTG(m);
   }

   updateGL();
}

void GLWidget::keyReleaseEvent(QKeyEvent *event)
{
    // Metode a implementar en el cas que es mogui la bola

}

void GLWidget::Zoom (double inOut) {
     esc->camGeneral.AmpliaWindow(inOut);//aumentar el tamaño del window equivale a un zoom out(inOut positivo)
     esc->camGeneral.CalculaMatriuProjection();
     updateGL();
}

void GLWidget::Pan(double dx, double dy) {
    esc->camGeneral.wd.pmin.x = esc->camGeneral.wd.pmin.x + dx;
    esc->camGeneral.wd.pmin.y = esc->camGeneral.wd.pmin.y + dy;
    esc->camGeneral.CalculaMatriuProjection();
    updateGL();
}


void GLWidget::newObjecte(Objecte * obj)
{
    point4 vrp;

    esc->addObjecte(obj);
    esc->CapsaMinCont3DEscena();
    vrp[0] = esc->capsaMinima.pmin[0]+(esc->capsaMinima.a/2.0);
    vrp[1] = esc->capsaMinima.pmin[1]+(esc->capsaMinima.h/2.0);
    vrp[2] = esc->capsaMinima.pmin[2]+(esc->capsaMinima.p/2.0);
    vrp[3] = 1.0;
    esc->setVRPCamera(cameraActual, vrp);
    if(cameraActual == true){
        esc->camGeneral.CalculWindow(esc->capsaMinima);
        esc->camGeneral.AmpliaWindow(-0.1);
        esc->camGeneral.CalculaMatriuProjection();
    }else{
    }

    updateGL();
}

void GLWidget::newPlaBase()
{
    PlaBase *plaBase;

    plaBase = this->newPlaBs();
    cT = plaBase->calculCapsa3D();//para el calculo de colisiones
    newObjecte(plaBase);
}

PlaBase* GLWidget::newPlaBs(){

    point4 v0  = point4( 0.5441, 0.0, 1.0, 1.0 );
    point4 v1  = point4( 0.5441, 0.0,-1.0, 1.0 );
    point4 v2  = point4(-0.5441, 0.0,-1.0, 1.0 );
    point4 v3  = point4(-0.5441, 0.0, 1.0, 1.0 );

    color4 cv0 = color4( 1.0, 1.0, 1.0, 1.0 ); //white
    color4 cv1  = color4( 1.0, 0.0, 0.0, 1.0 ); //red
    color4 cv2  = color4( 1.0, 1.0, 0.0, 1.0 ); //yellow
    color4 cv3  = color4( 0.0, 1.0, 0.0, 1.0 ); //green

    vec3 ka = vec3(0.0, 0.05, 0.0);
    vec3 kd = vec3(0.4, 0.5, 0.4);
    vec3 ke = vec3(0.04, 0.7, 0.04);
    float kre = 0.078125 * 128;

    Material *mat = new Material(ka, kd, ke, kre);

    PlaBase *plaBase = new PlaBase(v0, v1, v2, v3, cv0, cv1, cv2, cv3, mat);
    return plaBase;
}

void GLWidget::newObj(QString fichero)
{
    // Metode que carrega un fitxer .obj llegit de disc

    TaulaBillar *taulabillar = new TaulaBillar(fichero);
    newObjecte(taulabillar);
}

void GLWidget::newBola()
{

    Bola *bolablanca = new Bola(0.0, 0.03075, 0.5, tipoShading);
    newObjecte(bolablanca);
}

void GLWidget::newConjuntBoles()
{
    point4 vrp;
    ConjuntBoles *conjuntboles = new ConjuntBoles(tipoShading);

    esc->conjuntBoles = conjuntboles;
    for(int i=0; i<QUANTITAT_BOLES; i++){
        esc->listaObjectes.push_back(conjuntboles->llista_boles[i]);
        listaCapsasConjuntBoles.push_back(conjuntboles->llista_boles[i]->calculCapsa3D());
    }

    esc->CapsaMinCont3DEscena();
    vrp[0] = esc->capsaMinima.pmin[0]+(esc->capsaMinima.a/2.0);
    vrp[1] = esc->capsaMinima.pmin[1]+(esc->capsaMinima.h/2.0);
    vrp[2] = esc->capsaMinima.pmin[2]+(esc->capsaMinima.p/2.0);
    vrp[3] = 1.0;
    esc->setVRPCamera(cameraActual, vrp);
    if(cameraActual == true){
        esc->camGeneral.CalculWindow(esc->capsaMinima);
        esc->camGeneral.AmpliaWindow(-0.1);
        esc->camGeneral.CalculaMatriuProjection();
    }else{
    }

    updateGL();
}


    void GLWidget::newSalaBillar()
    {
        PlaBase *plaBase = this->newPlaBs();
        esc->addObjecte(plaBase);
        cT = plaBase->calculCapsa3D();//para el calculo de colisiones

        Bola *bolab = new Bola(0.0, 0.03075, 0.5,tipoShading);
        esc->addObjecte(bolab);

        ConjuntBoles *conjuntboles = new ConjuntBoles(tipoShading);
        esc->conjuntBoles = conjuntboles;
        for(int i=0; i<QUANTITAT_BOLES; i++){
            esc->listaObjectes.push_back(conjuntboles->llista_boles[i]);
            listaCapsasConjuntBoles.push_back(conjuntboles->llista_boles[i]->calculCapsa3D());
        }

        esc->CapsaMinCont3DEscena();
        point4 vrp;
        vrp[0] = esc->capsaMinima.pmin[0]+(esc->capsaMinima.a/2.0);
        vrp[1] = esc->capsaMinima.pmin[1]+(esc->capsaMinima.h/2.0);
        vrp[2] = esc->capsaMinima.pmin[2]+(esc->capsaMinima.p/2.0);
        vrp[3] = 1.0;

        esc->setVRPCamera(cameraActual, vrp);

        esc->camGeneral.CalculWindow(esc->capsaMinima);
        esc->camGeneral.AmpliaWindow(-0.1);
        esc->camGeneral.CalculaMatriuProjection();

        updateGL();
    }

// Metode per iniciar la dinàmica del joc
void GLWidget::Play()
{

}
