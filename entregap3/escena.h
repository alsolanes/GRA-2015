#ifndef ESCENA_H
#define ESCENA_H

#include <cmath>
#include <iostream>
#include <stdlib.h>

#include <list>
#include <vector>
#include <string>
#include <stdio.h>


#include <Common.h>
#include <objecte.h>
#include <taulabillar.h>
#include <plabase.h>
#include <bola.h>
#include <conjuntboles.h>
#include <camera.h>
#include <math.h>
#include <llum.h>
#include <QKeyEvent>
#include <conjuntllums.h>

#define VELOCITAT 0.03

using namespace std;

class Escena
{
public:
    Escena(int vpa, int vph);
    ~Escena();

    void addObjecte(Objecte *obj);
    void aplicaTG(mat4 m);

    void aplicaTGCentrat(mat4 m);
    void reset();

    void draw(bool cameraActual);
    void CapsaMinCont3DEscena();

    void iniCamera(bool camGen, int vpa, int vph);
    void setAnglesCamera(bool camGeneral, float angX, float angY, float angZ);
    void setVRPCamera(bool camGeneral, point4 vrp);
    void setWindowCamera(bool camGeneral, bool retallat, Capsa2D window);
    void setDCamera(bool camGeneral, float d);
    void computeCollisions(Capsa3D cb, Capsa3D cT, vec3 ctrB, vector<Capsa3D> listaCapsasConjuntBoles, QKeyEvent *event);
    void setAmbientToGPU(QGLShaderProgram *program);
    void setLlumiTexturaToGPU(QGLShaderProgram *program, bool teTextura);

    void move(bool cameraGeneral, int dir);
    bool canMove(Capsa3D capsa, vec3 posicio);
    bool isOnPlaBase(vec3 posicio);

    QGLShaderProgram *pr;
    // Capsa contenedora de l'escena
    Capsa3D capsaMinima;

    TaulaBillar *taulaBillar;
    PlaBase *plaBase;
    Bola *bola = NULL;
    ConjuntBoles *conjuntBoles;
    Camera camGeneral;
    Camera camPrimeraP;
    vector<Objecte*> llista_objectes;
    double dzP = 0.01;
    double dzN = -0.01;
    double dxP = 0.01;
    double dxN = -0.01;

    vec4 llumAmbient;
    ConjuntLlums *conjuntLlums;
    bool teTextura = true;

};

#endif // ESCENA_H
