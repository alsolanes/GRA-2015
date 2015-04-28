#include <math.h>

#include <glwidget.h>
#include <QString>


GLWidget::GLWidget(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)

{
    setFocusPolicy( Qt::StrongFocus );
    esc = new Escena();

    xRot = 0;
    yRot = 0;
    zRot = 0;

    a = 20.0;
    h = 20.0;
    p = 20.0;

    clearColor = Qt::black;
    qtGreen = QColor::fromCmykF(0.40, 0.0, 1.0, 0.0);
    qtPurple = QColor::fromCmykF(0.39, 0.39, 0.0, 0.0);

    program = 0;
    moviment = false;
    //afegit p2
    cameraActual = true;
}


GLWidget::~GLWidget()
{
    makeCurrent();
    delete esc;
}


// Create a GLSL program object from vertex and fragment shader files
void
GLWidget::InitShader(const char* vShaderFile, const char* fShaderFile)
{           

    QGLShader *vshader = new QGLShader(QGLShader::Vertex, this);
    QGLShader *fshader = new QGLShader(QGLShader::Fragment, this);

    // Compilació del vertex shader
    vshader->compileSourceFile(vShaderFile);
    fshader->compileSourceFile(fShaderFile);

    program = new QGLShaderProgram(this);
    program->addShader(vshader);
    program->addShader(fshader);

    program->bindAttributeLocation("vPosition", PROGRAM_VERTEX_ATTRIBUTE);
    program->bindAttributeLocation("vColor", PROGRAM_COLOR_ATTRIBUTE);

    // muntatge del shader en el pipeline gràfic per a ser usat
    program->link();

    // unió del shader al pipeline gràfic
    program->bind();
}

void GLWidget::initShadersGPU()
{
    // Carrega dels shaders i posa a punt per utilitzar els programes carregats a la GPU
   InitShader( "://vshader1.glsl", "://fshader1.glsl" );

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
        angle += 360 * 16;
    while (angle > 360 * 16)
        angle -= 360 * 16;
}

void GLWidget::setXRotation(int angle) {
    Camera *camActual;
    if(cameraActual) camActual = esc->camGeneral;
    else camActual = esc->camPrimeraP;
    qNormalizeAngle(angle);
    xRot += camActual->vs.angx;
    if (angle != xRot) {
        xRot = angle;
        update();
    }
}

void GLWidget::setYRotation(int angle) {
    Camera *camActual;
    if(cameraActual) camActual = esc->camGeneral;
    else camActual = esc->camPrimeraP;
    qNormalizeAngle(angle);
    yRot += camActual->vs.angy;
    if (angle != yRot) {
        yRot = angle;
        update();
    }
}

void GLWidget::setZRotation(int angle) {
    Camera *camActual;
    if(cameraActual) camActual = esc->camGeneral;
    else camActual = esc->camPrimeraP;
    qNormalizeAngle(angle);
    yRot += camActual->vs.angy;
    if (angle != yRot) {
        yRot = angle;
        update();
    }
}

void GLWidget::pan(int dx, int dy){
    if(cameraActual) esc->camGeneral->pan(dx, dy);
    else esc->camPrimeraP->pan(dx, dy);
}

void GLWidget::zoom(int positiu){
    if(cameraActual) esc->camGeneral->zoom(positiu);
    else esc->camPrimeraP->zoom(positiu);
}


void GLWidget::initializeGL()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    //std::cout<<"Estic inicialitzant el shaders"<<std::ends;
    initShadersGPU();

    glClearColor(clearColor.redF(), clearColor.greenF(), clearColor.blueF(), clearColor.alphaF());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

void GLWidget::paintGL()
{
   glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

   esc->draw();
}


void GLWidget::resizeGL(int width, int height)
{
    int side = qMin(width, height);
    glViewport((width - side) / 2, (height - side) / 2, side, side);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
#ifdef QT_OPENGL_ES_1
    glOrthof(-1.5, +1.5, -1.5, +1.5, 0.0, 15.0);
#else
    glOrtho(-1.5, +1.5, -1.5, +1.5, 0.0, 15.0);
#endif
    glMatrixMode(GL_MODELVIEW);


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
        setXRotation(xRot + 1 * dy);
        setYRotation(yRot + 1 * dx);
    }

    lastPos = event->pos();
    esc->setAnglesCamera(cameraActual, xRot, yRot, zRot);
}


void GLWidget::keyPressEvent(QKeyEvent *event)
{
    // Check if panning mode is activated
    bool panMode = event->modifiers().testFlag(Qt::AltModifier);
    switch ( event->key() )
    {
    case Qt::Key_Up:
        if (panMode)
            pan(0, 1);
        else {
            esc->move(cameraActual,1);
            if (!cameraActual){
                esc->setVRPCamera(cameraActual, esc->bola->capsa.centre);
            }
        }
        break;
    case Qt::Key_Down:
        if (panMode)
            pan(0, -1);
        else {
            esc->move(cameraActual,2);
            if (!cameraActual){
                esc->setVRPCamera(cameraActual, esc->bola->capsa.centre);
            }
        }
        break;
    case Qt::Key_Left:
        if (panMode)
            pan(-1, 0);
        else {
            esc->move(cameraActual,3);
            if (!cameraActual){
                esc->setVRPCamera(cameraActual, esc->bola->capsa.centre);
            }
        }
        break;
    case Qt::Key_Right:
        if (panMode)
            pan(1, 0);
        else {
            esc->move(cameraActual,4);
            if (!cameraActual){
                esc->setVRPCamera(cameraActual, esc->bola->capsa.centre);
            }
        }
        break;
    case Qt::Key_Plus:  // ampliem
        zoom(-1);
        break;
    case Qt::Key_Minus: //reduim
        zoom(1);
        break;
    case Qt::Key_B: //mostra camera 1era P
        cameraActual = false;
        esc->setVRPCamera(cameraActual, esc->bola->capsa.centre);
        esc->camPrimeraP->toGPU();
        break;
    case Qt::Key_T: //mostra camera general
        cameraActual = true;
        esc->camGeneral->toGPU();
        break;
    case Qt::Key_Tab: //si estavem a camGeneral, passem a camPrimeraP, i al revés
        cameraActual = !cameraActual;
        if (!cameraActual){
            esc->setVRPCamera(cameraActual, esc->bola->capsa.centre);
            esc->camPrimeraP->toGPU();
        }else{
            esc->camGeneral->toGPU();
        }
        break;
    case Qt::Key_L: //for debug purposes
        // print location of white ball
        cout << "Coordenades:" << esc->bola->capsa.pmin.x << " "<< esc->bola->capsa.pmin.y << " " << esc->bola->capsa.pmin.z << endl;
    }
    updateGL();
}

void GLWidget::keyReleaseEvent(QKeyEvent *event)
{
}


void GLWidget::newObjecte(Objecte * obj)
{
    esc->addObjecte(obj);
    obj->toGPU(program);
    updateGL();
}

void GLWidget::newPlaBase()
{
    // Metode que crea un objecte PlaBase poligon amb el punt central al (0,0,0) i perpendicular a Y=0
    PlaBase *plaBase;
    plaBase = new PlaBase();
    newObjecte(plaBase);
}

void GLWidget::newObj(QString fichero)
{
    // Metode que carrega un fitxer .obj llegit de disc
    TaulaBillar *obj;

    obj = new TaulaBillar(fichero);
    newObjecte(obj);
}

void GLWidget::newBola()
{
    // Metode que crea la Bola blanca de joc
    Bola *bol;
    bol = new Bola();
    newObjecte(bol);
}

void GLWidget::newConjuntBoles()
{
    // Metode que crea les 15 Boles del billar america
    ConjuntBoles *conjuntboles;
    conjuntboles = new ConjuntBoles();
    conjuntboles->toGPU(program);
    esc->addObjecte(conjuntboles);
}


void GLWidget::newTaulaBillar(){
    QString fichero("/Users/aleix/GRA-2015/BillarPractica1/resources/taula.obj");

    TaulaBillar *obj;
    obj = new TaulaBillar(fichero);
    newObjecte(obj);
}

/**
 * Sets the whole scene for the start of a new game.
 */
void GLWidget::newSalaBillar()
{
    // Metode que construeix tota la sala de billar: taula, 15 boles i bola blanca

    // Create
    newPlaBase();

    newBola();

    newConjuntBoles();


    esc->plaBase->aplicaTG(Scale(4., 1., 8.));

    esc->bola->aplicaTG(Translate(0.25, 0.25, -6) * Scale(0.25, 0.25, 0.25));
    esc->conjuntBoles->aplicaTG(Translate(0., 0.25, 4) * Scale(0.25, 0.25, 0.25));

    esc->CapsaMinCont3DEscena();
    esc->iniCamera(true, this->size().width(), this->size().height(), program);
    if(cameraActual) esc->camGeneral->toGPU();
    else esc->camPrimeraP->toGPU();

    updateGL();
}

// Metode per iniciar la dinàmica del joc
void GLWidget::Play()
{

}


