#include "conjuntboles.h"

ConjuntBoles::ConjuntBoles()
{
    int index_bola;
    for(int i = 0; i<QUANTITAT_BOLES; i++)
        llista_boles[i] = new Bola();
    index_bola = 0;

    for(int i=0;i<5;i++)
        for(int j=0;j<5-i;j++){
            points_boles[index_bola] = new vec4(i+j,0.0,2*i,1.0);
            index_bola++;
        }

    for (int i=0; i<QUANTITAT_BOLES; i++)
        llista_boles[i]->aplicaTG(Translate(*points_boles[i]));

}

ConjuntBoles::~ConjuntBoles()
{
    for (int i=0; i<QUANTITAT_BOLES; i++)
        delete this->llista_boles[i];
}

void ConjuntBoles::aplicaTG(mat4 m){
    for (int i=0; i<QUANTITAT_BOLES; i++)
        if (llista_boles[i] != NULL)
            llista_boles[i]->aplicaTG(m);
}

void ConjuntBoles::aplicaTGCentrat(mat4 m){
    for (int i=0; i<QUANTITAT_BOLES; i++)
        if (llista_boles[i] != NULL)
            llista_boles[i]->aplicaTGCentrat(m);
}

void ConjuntBoles::draw(){
    for(int i=0;i<QUANTITAT_BOLES;i++)
        if (llista_boles[i] != NULL)
            llista_boles[i]->draw();
}

void ConjuntBoles::toGPU(QGLShaderProgram *prog){
    for(int i=0; i<QUANTITAT_BOLES; i++)
        if(llista_boles[i] != NULL)
            llista_boles[i]->toGPU(prog);
}
