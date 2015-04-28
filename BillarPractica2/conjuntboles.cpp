#include "conjuntboles.h"
#include "sstream"

ConjuntBoles::ConjuntBoles() : Objecte(0)
{
    cout << "ConjuntBoles:: Constructor" << endl;
    //definim les textures de les boles
    for(int i = 0; i<QUANTITAT_BOLES;i++)
    {
        int a = i+1;
        stringstream ss;
        ss << a;
        QString str = QString::fromStdString(ss.str());
        texture_routes[i] = "://resources/Bola"+str+".jpg";
    }

    int index_bola = 0;

    for(int i=0;i<5;i++){
        for(int j=0;j<i+1;j++){
            points_boles[index_bola] = new vec4(-i+j*2,0.0,2*i,1.0);
            index_bola++;
        }
    }

    for(int i = 0; i<QUANTITAT_BOLES; i++){
        llista_boles[i] = new Bola(texture_routes[i]);
        llista_boles[i]->aplicaTG(Translate(*points_boles[i]));
    }
    capsa = calculCapsa3D();
    cout << "ConjuntBoles:: Fi Constructor" << endl;
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
    mat4 T1 = Translate(-capsa.centre.x, -capsa.centre.y, -capsa.centre.z);
    mat4 T2 = Translate(capsa.centre.x, capsa.centre.y, capsa.centre.z);
    for(int i=0; i<QUANTITAT_BOLES; i++)
        aplicaTG(T2*m*T1);
    capsa = calculCapsa3D();
}

void ConjuntBoles::aplicaTGPoints(mat4 m)
{
    for(int i=0; i < QUANTITAT_BOLES; i++)
        llista_boles[i]->aplicaTGPoints(m);

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

Capsa3D ConjuntBoles::calculCapsa3D() {
    Capsa3D capsa, capsaAux;

    vec3 puntMin, puntMax; //centremin, centremax
    float maxA, maxH, maxP;
    maxA = maxH = maxP = 0;
    capsaAux = llista_boles[0]->capsa;
    capsaAux.pmin = capsaAux.pmin;
    puntMin = capsaAux.pmin = puntMax;


    for (int i=0; i<QUANTITAT_BOLES; i++){
        capsaAux = llista_boles[i]->capsa;
        puntMin.x = puntMin.x > capsaAux.pmin.x? capsaAux.pmin.x: puntMin.x;
        puntMax.x = puntMax.x < capsaAux.pmin.x? capsaAux.pmin.x: puntMax.x;
        puntMin.y = puntMin.y > capsaAux.pmin.y? capsaAux.pmin.y: puntMin.y;
        puntMax.y = puntMax.y < capsaAux.pmin.y? capsaAux.pmin.y: puntMax.y;
        puntMin.z = puntMin.z > capsaAux.pmin.z? capsaAux.pmin.z: puntMin.z;
        puntMax.z = puntMax.z < capsaAux.pmin.z? capsaAux.pmin.z: puntMax.z;
        maxA = maxA < capsaAux.a? capsaAux.a: maxA;
        maxH = maxH < capsaAux.h? capsaAux.h: maxH;
        maxP = maxP < capsaAux.p? capsaAux.p: maxP;
    }

    capsa.a = fabs(puntMax.x - puntMin.x);
    capsa.h = fabs(puntMax.y - puntMin.y);
    capsa.p = fabs(puntMax.z - puntMin.z);
    capsa.pmin = puntMin;
    capsa.centre = capsa.pmin + vec3(capsa.a/2, capsa.h/2, capsa.p/2);

    return capsa;
}

void ConjuntBoles::toOrigin(){
    for(int i = 0; i<QUANTITAT_BOLES;i++)
        llista_boles[i]->aplicaTG(Translate(-capsa.centre));
    //recalculem la capsa ja que hem modificat la posició
    capsa = calculCapsa3D();
}
