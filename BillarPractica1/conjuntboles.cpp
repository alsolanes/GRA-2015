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
        for(int j=0;j<5-i;j++){
            points_boles[index_bola] = new vec4(i+j*2,0.0,2*i,1.0);
            index_bola++;
        }
    }

    for(int i = 0; i<QUANTITAT_BOLES; i++){
        llista_boles[i] = new Bola(texture_routes[i]);
        llista_boles[i]->aplicaTG(Translate(*points_boles[i]));
    }
    cout << "ConjuntBoles:: Fi Constructor" << endl;
}


ConjuntBoles::~ConjuntBoles()
{

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
    vec3 pmin, pmax, bolamin, bolamax;
    pmin = llista_boles[0]->capsa.pmin;
    pmax = pmin + vec3(llista_boles[0]->capsa.a, llista_boles[0]->capsa.h, llista_boles[0]->capsa.p);
    //mirem els punts minims i màxims per calcular la capsa3d
    for(int i = 1; i<QUANTITAT_BOLES;i++){
        bolamin = llista_boles[i]->capsa.pmin;
        bolamax = bolamin + vec3(llista_boles[i]->capsa.a, llista_boles[i]->capsa.h, llista_boles[i]->capsa.p);

        pmin.x = bolamin.x < pmin.x ? bolamin.x : pmin.x;
        pmax.x = bolamax.x > pmax.x ? bolamax.x : pmax.x;

        pmin.y = bolamin.y < pmin.y ? bolamin.y : pmin.y;
        pmax.y = bolamax.y > pmax.y ? bolamax.y : pmax.y;

        pmin.z = bolamin.z < pmin.z ? bolamin.z : pmin.z;
        pmax.z = bolamax.z > pmax.z ? bolamax.z : pmax.z;
    }

    Capsa3D capsa;
    capsa.a = fabs(pmax.x - pmin.x);
    capsa.h = fabs(pmax.y - pmin.y);
    capsa.p = fabs(pmax.z - pmin.z);
    capsa.centre = pmin + vec3(capsa.a/2, capsa.h/2, capsa.p/2);
    capsa.pmin = pmin;
    return capsa;
}

void ConjuntBoles::toOrigin(){
    for(int i = 0; i<QUANTITAT_BOLES;i++)
        llista_boles[i]->aplicaTG(Translate(-capsa.centre));
    //recalculem la capsa ja que hem modificat la posició
    capsa = calculCapsa3D();
}
