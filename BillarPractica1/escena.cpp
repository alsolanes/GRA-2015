#include "escena.h"

Escena::Escena()
{
    // Capsa minima contenidora provisional: S'ha de fer un recorregut dels objectes de l'escenes
    capsaMinima.pmin[0] = 0; capsaMinima.pmin[1] = 0; capsaMinima.pmin[2]=0;
    capsaMinima.a = 1; capsaMinima.h = 1; capsaMinima.p = 1;

    taulaBillar = NULL;
    plaBase = NULL;
    bola = NULL;
    conjuntBoles = NULL;
}

Escena::~Escena()
{
    // Cal anar fent delete dels objectes que se'l hagi fet new
   delete this->taulaBillar;
   delete this->plaBase;
   delete this->bola;
   delete this->conjuntBoles;
}

void Escena::addObjecte(Objecte *obj) {
    if (dynamic_cast<TaulaBillar*>(obj))
        this->taulaBillar = (TaulaBillar*)obj;
    else if(dynamic_cast<PlaBase*>(obj))
        this->plaBase = (PlaBase*)obj;
    else if(dynamic_cast<Bola*>(obj))
        this->bola = (Bola*)obj;
}
void Escena::addConjuntBoles(ConjuntBoles *conjunt_boles){
    this->conjuntBoles = conjunt_boles;

}

void Escena::CapsaMinCont3DEscena()
{
    // Metode a implementar
}

void Escena::aplicaTG(mat4 m) {

    // Metode a modificar

    if (taulaBillar!=NULL)
        taulaBillar->aplicaTG(m);
    if (plaBase!=NULL)
        plaBase->aplicaTG(m);
    if (bola!=NULL)
        bola->aplicaTG(m);
    if (conjuntBoles != NULL)
        conjuntBoles->aplicaTG(m);

}

void Escena::aplicaTGCentrat(mat4 m) {

    // Metode a modificar

    if (taulaBillar!=NULL)
        taulaBillar->aplicaTGCentrat(m);
    if (plaBase!=NULL)
        plaBase->aplicaTGCentrat(m);
    if (bola!=NULL)
        bola->aplicaTGCentrat(m);
    if (conjuntBoles!=NULL)
        conjuntBoles->aplicaTGCentrat(m);
}

void Escena::draw() {

    // Metode a modificar

    if (taulaBillar!=NULL)
        taulaBillar->draw();
    if (plaBase != NULL)
        plaBase->draw();
    if (bola != NULL)
        bola->draw();
    if(conjuntBoles!=NULL)
        conjuntBoles->draw();
}



