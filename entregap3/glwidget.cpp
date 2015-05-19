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

    shaderActual = "Flat";
    esc->teTextura = false;
    program = 0;
    //cameraActual = true;
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
//    QGLShader *vshader = new QGLShader(QGLShader::Vertex, this);
//    QGLShader *fshader = new QGLShader(QGLShader::Fragment, this);

    vshaderFlatGouraud = new QGLShader(QGLShader::Vertex, this);
    fshaderFlatGouraud = new QGLShader(QGLShader::Fragment, this);
    vshaderFlatGouraud->compileSourceFile("://vshaderFlatGouraud.glsl");
    fshaderFlatGouraud->compileSourceFile("://fshaderFlatGouraud.glsl");

    vshaderPhong = new QGLShader(QGLShader::Vertex, this);
    fshaderPhong = new QGLShader(QGLShader::Fragment, this);
    vshaderPhong->compileSourceFile("://vshaderPhong.glsl");
    fshaderPhong->compileSourceFile("://fshaderPhong.glsl");

    vshaderToon = new QGLShader(QGLShader::Vertex, this);
    fshaderToon = new QGLShader(QGLShader::Fragment, this);
    vshaderToon->compileSourceFile("://vshaderToon.glsl");
    fshaderToon->compileSourceFile("://fshaderToon.glsl");

    program = new QGLShaderProgram(this);

    //segons el shader que tinguem en aquest moment iniciarem un shader o un altre
    //flat i gouraud comparteixen shader
    if(shaderActual == "Flat" || shaderActual == "Gouraud"){
        initFlatGouraud();
    }else if(shaderActual == "Phong"){
        initPhong();
    }else if(shaderActual == "Toon"){
        initToon();
    }

    program->bindAttributeLocation("vPosition", PROGRAM_VERTEX_ATTRIBUTE);
    program->bindAttributeLocation("vColor", PROGRAM_COLOR_ATTRIBUTE);


    // muntatge del shader en el pipeline gràfic per a ser usat
    program->link();

    // unió del shader al pipeline gràfic
    program->bind();
}

void GLWidget::initFlatGouraud(){

    program->addShader(vshaderFlatGouraud);
    program->addShader(fshaderFlatGouraud);
}
void GLWidget::initPhong(){

    program->addShader(vshaderPhong);
    program->addShader(fshaderPhong);
}
void GLWidget::initToon(){

    program->addShader(vshaderToon);
    program->addShader(fshaderToon);
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
    //passem la llum ambient a la gpu i tambe les llums
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


void GLWidget::changeShader(QString newShader){

    QString tipoShadingOld = shaderActual;
    esc->teTextura = this->texturaActivada;
    if(shaderActual != newShader){
        if(((shaderActual == "Flat" || shaderActual == "Gouraud") && (newShader != "Flat" && newShader != "Gouraud")) ||
              ((shaderActual != "Flat" && shaderActual != "Gouraud"))  ){
            shaderActual = newShader;
            // eliminem els shaders i assignem el nou
            program->removeAllShaders();
            if(this->shaderActual == "Flat" || this->shaderActual =="Gouraud"){
                initFlatGouraud();
            }else if(this->shaderActual == "Phong"){
                initPhong();
            }else{
                initToon();
            }
            program->link();
            program->bind();
        }
        if((tipoShadingOld == "Flat" && newShader != "Flat") || (tipoShadingOld != "Flat" && newShader == "Flat")){
            shaderActual = newShader;
            newSalaBillar();
        }else{
            shaderActual = newShader;
        }
    }
}


void GLWidget::keyPressEvent(QKeyEvent *event)
{
    mat4 m;
    double angx;

   switch ( event->key() )
   {
   case Qt::Key_1:
       this->texturaActivada = false;
       if (event->modifiers() & Qt::AltModifier)
           this->texturaActivada = true;
       changeShader("Flat");
       break;

   case Qt::Key_2:
       this->texturaActivada = false;
       if (event->modifiers() & Qt::AltModifier)
           this->texturaActivada = true;
       changeShader("Gouraud");
       break;

   case Qt::Key_3:
       this->texturaActivada = false;
       if (event->modifiers() & Qt::AltModifier)
           this->texturaActivada = true;
       changeShader("Phong");
       break;

   case Qt::Key_4:
       this->texturaActivada = false;
       if (event->modifiers() & Qt::AltModifier)
         this->texturaActivada = true;
       changeShader("Toon");
       break;

   case Qt::Key_Up:
       if (event->modifiers() & Qt::AltModifier){
            pan(0, 0.01);
            break;
       }
       esc->move(cameraActual,3);
       break;
   case Qt::Key_Down:
        if (event->modifiers() & Qt::AltModifier){
          pan(0, -0.01);
          break;
        }
        esc->move(cameraActual,4);
        break;
   case Qt::Key_Left:
       if (event->modifiers() & Qt::AltModifier){
          pan(-0.01, 0);
          break;
       }
       esc->move(cameraActual,2);
       break;
   case Qt::Key_Right:
      if (event->modifiers() & Qt::AltModifier){
          pan(0.01, 0);
          break;
       }
       esc->move(cameraActual,1);
       break;
   case Qt::Key_Plus:
       zoom(-0.1);
       break;
   case Qt::Key_Minus:
       zoom(0.1);
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

void GLWidget::zoom (double positiu) {
     esc->camGeneral.zoom(positiu);
     updateGL();
}

void GLWidget::pan(double dx, double dy) {
    esc->camGeneral.pan(dx,dy);
    updateGL();
}


void GLWidget::newObjecte(Objecte * obj)
{
    point4 vrp;

    esc->addObjecte(obj);
    esc->CapsaMinCont3DEscena();
    vrp = esc->capsaMinima.centre;
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

    plaBase = new PlaBase();
    newObjecte(plaBase);
}



void GLWidget::newObj(QString fichero)
{
    // Metode que carrega un fitxer .obj llegit de disc

    TaulaBillar *taulabillar = new TaulaBillar(fichero);
    newObjecte(taulabillar);
}

void GLWidget::newBola()
{

    Bola *bolablanca = new Bola(0.0, 0.03075, 0.5, shaderActual);
    newObjecte(bolablanca);
}

void GLWidget::newConjuntBoles()
{
    point4 vrp;
    ConjuntBoles *conjuntboles = new ConjuntBoles(shaderActual);

    esc->conjuntBoles = conjuntboles;
    for(int i=0; i<QUANTITAT_BOLES; i++){
        esc->listaObjectes.push_back(conjuntboles->llista_boles[i]);
        listaCapsasConjuntBoles.push_back(conjuntboles->llista_boles[i]->calculCapsa3D());
    }

    esc->CapsaMinCont3DEscena();
    vrp = esc->capsaMinima.centre;
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
        PlaBase *plaBase = new PlaBase();
        esc->addObjecte(plaBase);
        cT = plaBase->calculCapsa3D();//para el calculo de colisiones

        Bola *bolab = new Bola(0.0, 0.03075, 0.5,shaderActual);
        esc->addObjecte(bolab);

        ConjuntBoles *conjuntboles = new ConjuntBoles(shaderActual);
        esc->conjuntBoles = conjuntboles;
        for(int i=0; i<QUANTITAT_BOLES; i++){
            esc->listaObjectes.push_back(conjuntboles->llista_boles[i]);
            listaCapsasConjuntBoles.push_back(conjuntboles->llista_boles[i]->calculCapsa3D());
        }

        esc->CapsaMinCont3DEscena();
        point4 vrp;
        vrp = esc->capsaMinima.centre;

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
