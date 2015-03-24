#include "taulabillar.h"

TaulaBillar::TaulaBillar(QString n) : Objecte(NumVerticesF)
{
    nom = n;
    Index = 0;
    tam = 1;

    xorig = 0;
    yorig = 0;
    zorig = 0;

    xRot = 0;
    yRot = 0;
    zRot = 0;

    readObj(n);

    Objecte::make();
    init_textura();
    capsa = calculCapsa3D();

    // Codi adhoc per a la taula carregada de fitxer taula.obj. Cal modificar-lo per a que sigui general
    double costat_llarg = capsa.a > capsa.p ? capsa.a : capsa.p;
    costat_llarg = capsa.h > costat_llarg ? capsa.h : costat_llarg;
    double escalaZ = 2.0 / costat_llarg;
    mat4 m = Scale(escalaZ, escalaZ, escalaZ)*Translate(-(capsa.pmin.x + capsa.a / 2.), -(capsa.pmin.y + capsa.h), -(capsa.pmin.z + capsa.p / 2.));
    aplicaTG(m);

    capsa = calculCapsa3D();
}

TaulaBillar::~TaulaBillar()
{

}

