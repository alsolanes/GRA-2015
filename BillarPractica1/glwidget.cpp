

#include <math.h>

#include <glwidget.h>
#include <QString>
#include <conjuntboles.h>


GLWidget::GLWidget(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)

{
    setFocusPolicy( Qt::StrongFocus );
    this->cameraActual = true;
    //passarem al constructor d'escena la mida del viewport
    esc = new Escena(this->size().width(),this->size().height());

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


void GLWidget::setXRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != xRot) {
        xRot = angle;
        update();
    }
}


void GLWidget::setYRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != yRot) {
        yRot = angle;
        update();
    }
}

void GLWidget::setZRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != zRot) {
        zRot = angle;
        update();
    }
}


void GLWidget::initializeGL()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    std::cout<<"Estic inicialitzant el shaders"<<std::ends;
    initShadersGPU();

    glClearColor(clearColor.redF(), clearColor.greenF(), clearColor.blueF(), clearColor.alphaF());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if(cameraActual){
        esc->camGeneral->toGPU(program);
    }
    else{}

}

void GLWidget::paintGL()
{
   glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
   if(cameraActual)
       esc->camGeneral->CalculaMatriuModelView();
   else{}
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
        setXRotation(xRot + 8 * dy);
        //setYRotation(yRot + 1 * dx);
    } else if (event->buttons() & Qt::RightButton) {
        //setXRotation(xRot + 1 * dy);
        //setZRotation(zRot + 1 * dx);
        setYRotation(yRot + 8 * dx);
    }
    lastPos = event->pos();
}


void GLWidget::keyPressEvent(QKeyEvent *event)
{
    // Metode a implementar
    switch ( event->key() )
    {
    case Qt::Key_Up:
        if(isMovePossible(0,0.01))
            esc->bola->aplicaTG(Translate(0.0, 0.01, 0.0));
        break;
    case Qt::Key_Down:
        if(isMovePossible(0,-0.01))
            esc->bola->aplicaTG(Translate(0.0, -0.01, 0.0));
        break;
    case Qt::Key_Left:
        if(isMovePossible(-0.01,0))
            esc->bola->aplicaTG(Translate(-0.01, 0.0, 0.0));
        break;
    case Qt::Key_Right:
        if(isMovePossible(-0.01,0))
            esc->bola->aplicaTG(Translate(-0.01, 0.0, 0.0));
        break;
    }
    updateGL();
}

bool GLWidget::isMovePossible(double x, double z){
    vec3 bola_min = esc->bola->capsa.pmin;
    vec3 pla_min = esc->plaBase->capsa.pmin;
    if((bola_min.x+x)>pla_min.x && (bola_min.x+x)<(pla_min.x+esc->plaBase->capsa.a))
       if((bola_min.z+z)<(pla_min.z+esc->plaBase->capsa.p) && (bola_min.z+z)>pla_min.z)
                return true;
    return false;
}

void GLWidget::keyReleaseEvent(QKeyEvent *event)
{
    // Metode a implementar en el cas que es mogui la bola

}



void GLWidget::adaptaObjecteTamanyWidget(Objecte *obj)
{
        // Metode a implementar
    Capsa3D capsa_escena = esc->capsaMinima;
    vec3 centre_escena = capsa_escena.pmin;
    mat4 T1 = Translate(centre_escena.x/(capsa_escena.a/2), centre_escena.y/(capsa_escena.h/2), centre_escena.z/(capsa_escena.p/2));
    mat4 S = Scale(1/(a/2), 1/(h/2), 1/(p/2));
    mat4 T2 = Translate(centre_escena.x, centre_escena.y, centre_escena.z);
    obj->aplicaTG(T1*S*T2);
}

void GLWidget::newObjecte(Objecte * obj)
{
    adaptaObjecteTamanyWidget(obj);
    obj->toGPU(program);
    esc->addObjecte(obj);

    updateGL();
}

void GLWidget::newPlaBase()
{
    // Metode que crea un objecte PlaBase poligon amb el punt central al (0,0,0) i perpendicular a Y=0

    // Metode a implementar
    newObjecte(new PlaBase());
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
     // Metode a implementar
    Bola *bol;
    bol = new Bola();
    newObjecte(bol);
}
void GLWidget::newConjuntBoles()
{
    // Metode que crea les 15 Boles del billar america
    // Metode a implementar
    ConjuntBoles *conjunt_boles;

    conjunt_boles = new ConjuntBoles();

    conjunt_boles->toGPU(program);
    esc->addObjecte(conjunt_boles);

    updateGL();
}
void GLWidget::newSalaBillar()
{
    newPlaBase();
    esc->plaBase->aplicaTG(Scale(5., 0., 10.));
    newBola();
    esc->bola->aplicaTG(Translate(0,0.03,.6)*Scale(0.3,0.3,0.3));
    newConjuntBoles();
    esc->conjuntBoles->aplicaTG(Translate(-0.1,0.03,-0.5)*Scale(0.3,0.3,0.3));

    esc->aplicaTG(RotateX(-90));
    esc->aplicaTG(RotateZ(-180));
    updateGL();

}

// Metode per iniciar la dinàmica del joc
void GLWidget::Play()
{

}
