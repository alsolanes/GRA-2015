#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <math.h>
#include <escena.h>
#include <bola.h>
#include <conjuntboles.h>
#include <material.h>

#include <QtWidgets>
#include <QGLWidget>

#include <QDir>


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

    bool cameraActual;



public slots:
    void newPlaBase();
    void newObj(QString fichero);
    void newBola();
    void newConjuntBoles();
    void newSalaBillar();

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
    void zoom (double inOut);
    void pan(double dx, double dy);
    void changeShader(QString newShader);

private:
    Escena *esc;

    bool texturaActivada;
    double xRot;
    double yRot;
    double zRot;
    float  a, p, h;

    QColor clearColor;
    QPoint lastPos;
    QColor qtGreen;
    QColor qtPurple;

    bool moviment;

    QGLShader *vertexFlatGouraud;
    QGLShader *fragmentFlatGouraud;
    QGLShader *vertexPhong;
    QGLShader *fragmentPhong;
    QGLShader *vertexToon;
    QGLShader *fragmentToon;

    // Programa de la GPU
    QGLShaderProgram *program;
    vector<Capsa3D> capses;
    QString shaderActual;

    //  Metode per a carregar de fitxers el vertex i el fragment shader
   void InitShaderGPU();

   void initFlatGouraud();
   void initPhong();
   void initToon();

    // Metode que carrega un nou objecte a l'escena
    void newObjecte(Objecte * obj);

};


#endif // GLWIDGET_H
