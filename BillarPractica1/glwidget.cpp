

#include <math.h>

#include <glwidget.h>
#include <QString>
#include <conjuntboles.h>


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

}

void GLWidget::paintGL()
{
   glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

   qNormalizeAngle(xRot);
   qNormalizeAngle(yRot);
   qNormalizeAngle(zRot);

   mat4 transform = ( RotateX( xRot / 16.0 ) *
                       RotateY( yRot / 16.0 ) *
                       RotateZ( zRot / 16.0 ) );

   // A modificar si cal girar tots els objectes
   esc->aplicaTGCentrat(transform);
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
    } else if (event->buttons() & Qt::RightButton) {
        setXRotation(xRot + 1 * dy);
        setZRotation(zRot + 1 * dx);
    }
    lastPos = event->pos();
}


void GLWidget::keyPressEvent(QKeyEvent *event)
{
    // Metode a implementar
    switch ( event->key() )
    {
    case Qt::Key_Up:
        esc->bola->aplicaTG(Translate(0.0, 0.01, 0.0));
        break;
    case Qt::Key_Down:
        esc->bola->aplicaTG(Translate(0.0, -0.01, 0.0));
        break;
    case Qt::Key_Left:
        esc->bola->aplicaTG(Translate(-0.01, 0.0, 0.0));
        break;
    case Qt::Key_Right:
        esc->bola->aplicaTG(Translate(-0.01, 0.0, 0.0));
        break;
    }
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
    PlaBase *plaBase = new PlaBase();
    plaBase->make();
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
     // Metode a implementar
    Bola *bol;
    bol = new Bola();
    newObjecte(bol);
}
void GLWidget::newConjuntBoles()
{
    // Metode que crea les 15 Boles del billar america
    // Metode a implementar
    // Metode que crea les 15 Boles del billar america
    ConjuntBoles *conjunt_boles;

    conjunt_boles = new ConjuntBoles();
    for (int i=0; i<15; i++) {
            adaptaObjecteTamanyWidget(conjunt_boles->llista_boles[i]);

    }
    conjunt_boles->toGPU(program);
    esc->addConjuntBoles(conjunt_boles);

    updateGL();
}
void GLWidget::newSalaBillar()
{
    // Metode que construeix tota la sala de billar: taula, 15 boles i bola blanca
    newPlaBase();
    newConjuntBoles();
    newBola();
    adaptaObjecteTamanyWidget(esc->bola);
    adaptaObjecteTamanyWidget(esc->plaBase);
    //CORREGIR
    esc->plaBase->aplicaTG(Scale(8., 1., 16.));

    mat4 transforma_bola_blanca = Translate(0., 0.25/10, -5/10.) * Scale(0.25, 0.25, 0.25);
    esc->bola->aplicaTG(transforma_bola_blanca);

    mat4 transforma_boles= Translate(0., 0.25/10, +2*sqrt(3.)/10.) * Scale(0.25, 0.25, 0.25);
    esc->conjuntBoles->aplicaTG(transforma_boles);

    esc->aplicaTG(RotateX(-90.));

    updateGL();
}

// Metode per iniciar la dinàmica del joc
void GLWidget::Play()
{

}
