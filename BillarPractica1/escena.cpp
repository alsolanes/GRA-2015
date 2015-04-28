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
    camGeneral = new Camera();
}

Escena::Escena(int viewportW, int viewportH)
{
    // Capsa minima contenidora provisional: S'ha de fer un recorregut dels objectes de l'escenes
    capsaMinima.pmin[0] = 0; capsaMinima.pmin[1] = 0; capsaMinima.pmin[2]=0;
    capsaMinima.a = 1; capsaMinima.h = 1; capsaMinima.p = 1;

    taulaBillar = NULL;
    plaBase = NULL;
    bola = NULL;
    conjuntBoles = NULL;
    iniCamera(true, viewportW, viewportH, prog);
    iniCamera(false, viewportW, viewportH, prog);
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
    if (dynamic_cast<TaulaBillar*>(obj) && taulaBillar==NULL){
        this->taulaBillar = (TaulaBillar*)obj;
        llista_objectes.push_back(taulaBillar);
    }
    else if(dynamic_cast<PlaBase*>(obj) && plaBase==NULL){
        this->plaBase = (PlaBase*)obj;
        llista_objectes.push_back(plaBase);
    }
    else if(dynamic_cast<Bola*>(obj) && bola==NULL){
        this->bola = (Bola*)obj;
        llista_objectes.push_back(bola);
    }
    else if(dynamic_cast<ConjuntBoles*>(obj) && conjuntBoles ==NULL){
        this->conjuntBoles = (ConjuntBoles*)obj;
        llista_objectes.push_back(conjuntBoles);
    }
    CapsaMinCont3DEscena();
}
//void Escena::addConjuntBoles(ConjuntBoles *conjunt_boles){
//    this->conjuntBoles = conjunt_boles;
//    CapsaMinCont3DEscena();
//}

void Escena::CapsaMinCont3DEscena()
{
    // Metode a implementar
    //punts generals mins i maxs
    vec3 pGmin, pGmax, pGminAux,pGmaxAux;
    for(unsigned int i=0;i<llista_objectes.size();i++){
        Capsa3D capsaAux = llista_objectes[i]->capsa;
        pGminAux = capsaAux.pmin;
        pGmaxAux = pGminAux + vec3(capsaAux.a, capsaAux.h, capsaAux.p);

        pGmin.x = pGmin.x > pGminAux.x ? pGminAux.x:pGmin.x;
        pGmin.y = pGmin.y > pGminAux.y ? pGminAux.y:pGmin.y;
        pGmin.z = pGmin.z > pGminAux.z ? pGminAux.z:pGmin.z;

        pGmax.x = pGmax.x < pGmaxAux.x ? pGmaxAux.x:pGmax.x;
        pGmax.y = pGmax.y < pGmaxAux.y ? pGmaxAux.y:pGmax.y;
        pGmax.z = pGmax.z < pGmaxAux.z ? pGmaxAux.z:pGmax.z;
    }
    capsaMinima.pmin = pGmin;
    capsaMinima.a = fabs(pGmin.x-pGmax.x);
    capsaMinima.h = fabs(pGmin.y-pGmax.y);
    capsaMinima.p = fabs(pGmin.z-pGmax.z);
    capsaMinima.centre = capsaMinima.pmin + vec3(capsaMinima.a/2, capsaMinima.h/2, capsaMinima.p/2);
}

void Escena::aplicaTG(mat4 m) {

    // Metode a modificar
    //recorrem la llista d'objectes i els hi apliquem la transformacio
    for(unsigned int i=0;i<llista_objectes.size();i++)
        llista_objectes[i]->aplicaTG(m);
}

void Escena::aplicaTGCentrat(mat4 m) {

    // Metode a modificar
    // matrius per tornar a l'origen(centrar)
    mat4 T1 = Translate(capsaMinima.centre.x, capsaMinima.centre.y, capsaMinima.centre.z);
    mat4 T2 = Translate(-capsaMinima.centre.x, -capsaMinima.centre.y, -capsaMinima.centre.z);
    // matrius de la transformacio a aplicar a cada objecte(recordar que primer s'aplica T2)
    mat4 mRes = T1*m*T2;
    //apliquem la transformacio a tots els objectes
    for(unsigned int i = 0; i < llista_objectes.size(); i++)
        llista_objectes[i]->aplicaTGCentrat(mRes);
    //recalculem la capsa
    CapsaMinCont3DEscena();
}

void Escena::draw() {

    // Metode a modificar
    //apliquem el draw a tots els objectes de la llista
    for(unsigned int i = 0; i< llista_objectes.size();i++)
        llista_objectes[i]->draw();
}

void Escena::draw(bool cameraActual) {

    // Metode a modificar
    //apliquem el draw a tots els objectes de la llista
    for(unsigned int i = 0; i< llista_objectes.size();i++){
        llista_objectes[i]->draw();
    }
}

//mètodes referents a la càmera
void Escena::iniCamera(bool camG,int ampladaViewport, int alcadaViewport, QGLShaderProgram *program){
    if (camG){
        point4 vrp = point4(0.0,0.0,0.0,1.0);
        camGeneral->piram.proj = PARALLELA;
        camGeneral->ini(ampladaViewport, alcadaViewport, capsaMinima);
        camGeneral->vs.obs = vec4(0.,20.,0.,1.0);

        setVRPCamera(true, vrp);
        setDCamera(true,20.);
        setAnglesCamera(true,-90.,0.,0.);
        camGeneral->CalculWindow(capsaMinima);
        camGeneral->piram.dant = 10.;//revisar mides
        camGeneral->piram.dpost = 30.;//revisar mides
        camGeneral->CalculaMatriuProjection();
    } else{

    }
}

void Escena::setAnglesCamera(bool camG, float angX, float angY, float angZ){
    if(camG){
        camGeneral->vs.angx = angX;
        camGeneral->vs.angy = angY;
        camGeneral->vs.angz = angZ;
        camGeneral->vs.vup = vec4(camGeneral->CalculVup(angX,angY, angZ),0.0);
        camGeneral->vs.obs = camGeneral->CalculObs(camGeneral->vs.vrp, camGeneral->piram.d, camGeneral->vs.angx, camGeneral->vs.angy);
        camGeneral->CalculaMatriuModelView();
    } else {

    }
}

void Escena::setVRPCamera(bool camG, point4 vrp){
    if(camG){
        camGeneral->vs.vrp = vrp;
        camGeneral->CalculaMatriuModelView();
    } else {

    }
}

void Escena::setWindowCamera(bool camG, bool retallat, Capsa2D window){
    if(camG){
        camGeneral->wd = window;
        if(retallat){
            this->camGeneral->CalculWindowAmbRetallat();
        }
        camGeneral->AjustaAspectRatioWd();
        camGeneral->CalculaMatriuProjection();
    } else {

    }
}

void Escena::setDCamera(bool camG, float d){
    if(camG){
        this->camGeneral->piram.d = d;
    } else {

    }
}
