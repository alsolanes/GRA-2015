#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <math.h>
#include <escena.h>

#include <QtWidgets>
#include <QGLWidget>
#include <QtOpenGL>
#include <QTime>


#define PROGRAM_VERTEX_ATTRIBUTE 0
#define PROGRAM_COLOR_ATTRIBUTE 1

class QGLShaderProgram;

class GLWidget : public QGLWidget
{
    Q_OBJECT

public:
    GLWidget(QWidget *parent = 0);
    ~GLWidget();

    QSize minimumSizeHint() const;
    QSize sizeHint() const;
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);
    //metodes p2 per fer panning i zoom
    void pan(int dx, int dy);
    void zoom(int positiu);

public slots:
    void newPlaBase();
    void newObj(QString fichero);
    void newBola();
    void newConjuntBoles();
    void newSalaBillar();
    void newTaulaBillar();
    // Metode per iniciar la dinàmica del joc
    void Play();

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);


private:
    Escena *esc;

    int xRot;
    int yRot;
    int zRot;
    float  a, p, h;

    QColor clearColor;
    QPoint lastPos;
    QColor qtGreen;
    QColor qtPurple;

    bool moviment;
    bool cameraActual; //cert quan s'ha de modificar la càmera general, fals quan s'ha de modificar la 1P

    // Programa de la GPU
    QGLShaderProgram *program;


    //  Metode per a carregar de fitxers el vertex i el fragment shader
   void InitShader( const char* vertexShaderFile,
                    const char* fragmentShaderFile );

   // Metode per inicialitzar els shaders de l'aplicacio
    void initShadersGPU();

    // Metode que carrega un nou objecte a l'escena
    void newObjecte(Objecte * obj);

};


#endif // GLWIDGET_H
