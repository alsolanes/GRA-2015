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

using namespace std;

class Escena
{
public:
    Escena();
    Escena(int viewportW, int viewportH);
    ~Escena();

    void addObjecte(Objecte *obj);
    void aplicaTG(mat4 m);

    void aplicaTGCentrat(mat4 m);
    void reset();

    void draw();
    void draw(bool cameraActual); //li passem el booleà per saber quina camera envia a gpu
    void CapsaMinCont3DEscena();


    //mètodes de la càmera
    void iniCamera(bool camGen,int ampladaViewport, int alcadaViewport, QGLShaderProgram *program);
    void setAnglesCamera(bool camGen, float angX, float angY, float angZ);
    void setVRPCamera(bool camGen, point4 vrp);
    void setWindowCamera(bool camGen, bool retallat, Capsa2D window);
    void setDCamera(bool camGen,float d);
    // Capsa contenedora de l'escena
    Capsa3D capsaMinima;

    QGLShaderProgram *prog;
    TaulaBillar *taulaBillar;
    PlaBase *plaBase;
    Bola *bola;
    ConjuntBoles *conjuntBoles;
    vector<Objecte *> llista_objectes;

    Camera *camGeneral;

};

#endif // ESCENA_H
