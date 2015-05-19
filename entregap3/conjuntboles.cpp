#include "conjuntboles.h"
#include "sstream"

ConjuntBoles::ConjuntBoles(QString tipoShading):Objecte(0)
{
    cout << "ConjuntBoles:: Constructor" << endl;
    //definim les textures de les boles
    for(int i = 0; i<QUANTITAT_BOLES;i++)
    {
        int a = i+1;
        std::stringstream ss;
        ss << a;
        QString str = QString::fromStdString(ss.str());
        texture_routes[i] = "://resources/Bola"+str+".jpg";
    }

    points_boles[0]=new vec4(0,0.03,-0.5,1.0);
    points_boles[1]=new vec4(0.03,0.03,-0.56,1.0);
    points_boles[2]=new vec4(-0.06,0.03,-0.62,1.0);
    points_boles[3]=new vec4(-0.03,0.03,-0.68,1.0);
    points_boles[4]=new vec4(0.09,0.03,-0.68,1.0);
    points_boles[5]=new vec4(0.06,0.03,-0.74,1.0);
    points_boles[6]=new vec4(0,0.03,-0.74,1.0);
    points_boles[7]=new vec4(0,0.03,-0.62,1.0);
    points_boles[8]=new vec4(-0.12,0.03,-0.74,1.0);
    points_boles[9]=new vec4(-0.03,0.03,-0.56,1.0);
    points_boles[10]=new vec4(0.06,0.03,-0.62,1.0);
    points_boles[11]=new vec4(0.03,0.03,-0.68,1.0);
    points_boles[12]=new vec4(-0.09,0.03,-0.68,1.0);
    points_boles[13]=new vec4(-0.06,0.03,-0.74,1.0);
    points_boles[14]=new vec4(0.12,0.03,-0.74,1.0);
    for (int i = 0; i<QUANTITAT_BOLES;i++){
        Bola* bola = new Bola(points_boles[i]->x, points_boles[i]->y, points_boles[i]->z,texture_routes[i],tipoShading);
        llista_boles.push_back(bola);
    }

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




