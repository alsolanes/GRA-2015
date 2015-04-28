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
#define VELOCITAT 0.3
#define DISTANCIA_1P 10.
#define ANGLE_1P -20
#define ALCADA_1P 3.

using namespace std;

class Escena
{
public:
    Escena();
    Escena(int a, int h);
    ~Escena();

    void addObjecte(Objecte *obj);
    void aplicaTG(mat4 m);

    void aplicaTGCentrat(mat4 m);
    void reset();

    void draw(bool camAct);
    void CapsaMinCont3DEscena();
    void move(bool cameraGeneral, int dir);

    // mètodes de la càmera
    void iniCamera(bool camGeneral, int ampladaViewport, int alcadaViewport, QGLShaderProgram *program);
    void setAnglesCamera(bool camGeneral, float angX, float angY, float angZ);
    void setVRPCamera(bool camGeneral, point4 vrp);
    void setWindowCamera(bool camGeneral, bool retallat, Capsa2D window);
    void setDCamera(bool camGeneral, float d);

    // Programa de la GPU
    QGLShaderProgram *program;

    // Capsa contenedora de l'escena
    Capsa3D capsaMinima;

    // Objectes de l'escena: a modificar. Ara nomes té un objecte: la taula de billar.
    // Cal afegir la bola blanca o el pla base per testejar o les 15 boles
    TaulaBillar *taulaBillar;
    PlaBase *plaBase;
    Bola *bola;
    ConjuntBoles *conjuntBoles;
    vector<Objecte *> llista_objectes;

    Camera *camGeneral;
    Camera *camPrimeraP;

private:
    bool canMove(Capsa3D capsa, vec3 posicio);
    bool isOnPlaBase(vec3 posicio);
};

#endif // ESCENA_H
