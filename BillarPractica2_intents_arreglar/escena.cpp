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

    camGeneral = NULL;
    camPrimeraP = NULL;
}

Escena::Escena(int amplada, int alcada)
{
    // Capsa minima contenidora provisional: S'ha de fer un recorregut dels objectes de l'escenes
    capsaMinima.pmin[0] = 0; capsaMinima.pmin[1] = 0; capsaMinima.pmin[2]=0;
    capsaMinima.a = 1; capsaMinima.h = 1; capsaMinima.p = 1;

    taulaBillar = NULL;
    plaBase = NULL;
    bola = NULL;
    conjuntBoles = NULL;

    iniCamera(true, amplada, alcada, this->program);
    iniCamera(false, amplada, alcada, this->program);
}


Escena::~Escena()
{
    // Cal anar fent delete dels objectes que se'l hagi fet new
   if (this->taulaBillar != NULL)
    delete this->taulaBillar;
   if (this->plaBase != NULL)
    delete this->plaBase;
   if (this->bola != NULL)
    delete this->bola;
   if (this->conjuntBoles != NULL)
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


void Escena::CapsaMinCont3DEscena()
{
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

    CapsaMinCont3DEscena();
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


void Escena::draw(bool cameraActual) {
    // Metode a modificar
    //apliquem el draw a tots els objectes de la llista
    if (taulaBillar!=NULL){
            taulaBillar->toGPU(program);
            if(cameraActual){
                    camGeneral->toGPU(program);
                }else{
                    camPrimeraP->toGPU(program);
                }
            taulaBillar->draw();
        }

        if (plaBase!=NULL){
            plaBase->texture->bind(0);
            plaBase->toGPU(program);
            if(cameraActual){
                    camGeneral->toGPU(program);
                }else{
                    camPrimeraP->toGPU(program);
                }
            plaBase->draw();
        }

        if (bola!=NULL){
            bola->texture->bind(0);
            bola->toGPU(program);
            if(cameraActual){
                camGeneral->toGPU(program);
            }else{
                camPrimeraP->toGPU(program);
            }
            bola->draw();
        }

        if (conjuntBoles!=NULL){
            for (int i=0; i<15; i++) {
                conjuntBoles->llista_boles[i]->texture->bind(0);
                conjuntBoles->llista_boles[i]->toGPU(program);
                if(cameraActual){
                    camGeneral->toGPU(program);
                }else{
                    camPrimeraP->toGPU(program);
                }
                conjuntBoles->llista_boles[i]->draw();
            }
        }
}


void Escena::move(bool cameraGeneral, int dir){
    Capsa3D capsaBola = bola->capsa;
    vec3 vecMoviment, posicioFinal;
    switch (dir)
    {
    case 1: //up
        if(cameraGeneral)
            vecMoviment = plaBase->vectorVertical();
        else
            vecMoviment = -normalize(bola->capsa.centre - conjuntBoles->capsa.centre);
        break;
    case 2: //down
        if(cameraGeneral)
            vecMoviment = -plaBase->vectorVertical();
        else
            vecMoviment = normalize(bola->capsa.centre - conjuntBoles->capsa.centre);
        break;
    case 3: //left
        if(cameraGeneral)
            vecMoviment = plaBase->vectorHoritzontal();
        else{
            vecMoviment = normalize(conjuntBoles->capsa.centre - bola->capsa.centre);
            float aux = vecMoviment.x;
            vecMoviment.x = vecMoviment.z;
            vecMoviment.z = -aux;
        }
        break;
    case 4: //right
        if(cameraGeneral)
            vecMoviment = -plaBase->vectorHoritzontal();
        else{
            vecMoviment = normalize(conjuntBoles->capsa.centre - bola->capsa.centre);
            float aux = vecMoviment.x;
            vecMoviment.x = -vecMoviment.z;
            vecMoviment.z = aux;
        }
        break;
    }
    vecMoviment *= VELOCITAT;
    posicioFinal = capsaBola.centre + vecMoviment;
    if (canMove(capsaBola,posicioFinal) && isOnPlaBase(posicioFinal))
        bola->aplicaTG(Translate(vecMoviment.x, 0, vecMoviment.z));
}

/*
 * Mètode que comprova les colisions mirant la capsa de la bola i la posició on es troba
 * Comprova bola a bola per evitar el quadrat que es crea a conjunt boles
 */
bool Escena::canMove(Capsa3D capsa, vec3 posicio){
    Capsa3D capsaBolaAux;
    vec3 minBlanca, minAux, maxBlanca, maxAux;

    minBlanca = vec3(posicio.x, posicio.y ,posicio.z);
    maxBlanca = vec3(posicio.x+capsa.a, posicio.y+capsa.h, posicio.z+capsa.p);

    for(int i=0; i<QUANTITAT_BOLES; i++){
        capsaBolaAux = conjuntBoles->llista_boles[i]->capsa;
        posicio = capsaBolaAux.centre;

        minAux = vec3(posicio.x,posicio.y, posicio.z);
        maxAux = vec3(posicio.x+capsaBolaAux.a, posicio.y+capsaBolaAux.h, posicio.z+capsaBolaAux.p);

        if (minBlanca.x < maxAux.x && maxBlanca.x > minAux.x &&
            minBlanca.y < maxAux.y && maxBlanca.y > minAux.y &&
            minBlanca.z < maxAux.z && maxBlanca.z > minAux.z)
            return false;
    }

    return true;
}


bool Escena::isOnPlaBase(vec3 pos){
    float radi = bola->capsa.a/2;
    Capsa3D c;
    vec3 up = plaBase->vectorVertical(), right = plaBase->vectorHoritzontal();
    vec3 pos2 = (pos - normalize(cross(up, right))*radi);
    vec3 minBlanca, maxBlanca, minPla, maxPla;

    minBlanca = vec3(pos2.x-radi, pos2.y-radi, pos2.z-radi);
    maxBlanca = vec3(pos2.x+radi, pos2.y+radi, pos2.z+radi);

    c = plaBase->capsa;
    vec3 posPla = c.centre;
    minPla = vec3(posPla.x-c.a/2, posPla.y-c.h/2, posPla.z-c.p/2);
    maxPla = vec3(posPla.x+c.a/2, posPla.y+c.h/2, posPla.z+c.p/2);

    if (minBlanca.x < maxPla.x && maxBlanca.x > minPla.x &&
            minBlanca.y <= maxPla.y && maxBlanca.y >= minPla.y &&
            minBlanca.z < maxPla.z && maxBlanca.z > minPla.z)
        return true;
    return false;
}
void Escena::iniCamera(bool camGen, int ampladaViewport, int alcadaViewport, QGLShaderProgram *program){
    this->program = program;
    this->camGeneral = new Camera();
    this->camPrimeraP = new Camera();
    if(camGen){
        camGeneral->ini(ampladaViewport, alcadaViewport, capsaMinima, this->program);
        camGeneral->piram.proj = PARALLELA;
        camGeneral->vs.obs = vec4(0.0, 20.0, 0.0, 1.0);
        setVRPCamera(true,point4(0,0,0,1));
        setDCamera(true, 20.0);
        setAnglesCamera(true, -90, 0,0);
        camGeneral->CalculWindow(capsaMinima);
        camGeneral->piram.dant = 0.1;
        camGeneral->piram.dpost = 30.0;
        camGeneral->CalculaMatriuProjection();
    }else{
        camPrimeraP->piram.proj = PERSPECTIVA;
        camPrimeraP->ini(ampladaViewport, alcadaViewport, capsaMinima, this->program);

        camPrimeraP->vs.vup = vec4(0.0, 1.0, 0.0, 0.0);
        camPrimeraP->vs.obs = vec4(0.0, 0.0307474, 0.6, 1.0);
        point4 vrp = point4(0.0, 0.0307474, 0.5, 1.0);
        setVRPCamera(false, vrp);
        setDCamera(false, 1.3);

        camPrimeraP->wd.pmin.x = -0.1255;
        camPrimeraP->wd.pmin.y = -0.0891265;
        camPrimeraP->wd.a = 0.251;
        camPrimeraP->wd.h = 0.188253;
        camPrimeraP->piram.dant = 0.34;
        camPrimeraP->piram.dpost= 1.7;
        camPrimeraP->CalculaMatriuProjection();
    }
}

void Escena::setAnglesCamera(bool camGeneral, float angX, float angY, float angZ){
    Camera *camActual;
    if(camGeneral) camActual = this->camGeneral;
    else camActual = this->camPrimeraP;

    camActual->defineAngles(angX,angY,angZ);
    camActual->vs.obs = camActual->CalculObs(camActual->vs.vrp, camActual->piram.d, camActual->vs.angx, camActual->vs.angy);
    camActual->vs.vup = camActual->CalculVup(angX, angY, angZ);
    camActual->CalculaMatriuModelView();
    //camActual->setModelViewToGPU();
    camActual->CalculaMatriuProjection();
    //camActual->setProjectionToGPU();
}

void Escena::setVRPCamera(bool camGeneral, point4 vrp){
    if(camGeneral){
        this->camGeneral->vs.vrp = vrp;
        this->camGeneral->CalculaMatriuModelView();
        //this->camGeneral->setModelViewToGPU();
        //this->camGeneral->CalculaMatriuProjection();
        //this->camGeneral->setProjectionToGPU();
    }
    else{
        camPrimeraP->vs.vrp = vrp;
        camPrimeraP->CalculaMatriuModelView();
    }
}

void Escena::setWindowCamera(bool camGeneral, bool retallat, Capsa2D window){
    if(camGeneral){
        this->camGeneral->wd = window;
        if (retallat)
            this->camGeneral->CalculWindowAmbRetallat();
        this->camGeneral->AjustaAspectRatioWd();
        this->camGeneral->CalculaMatriuProjection();
        //this->camGeneral->setProjectionToGPU();
    }
    else {
        this->camPrimeraP->wd = window;
        this->camPrimeraP->CalculAngleOberturaHoritzontal();
        this->camPrimeraP->CalculAngleOberturaVertical();
        if (retallat)
            this->camPrimeraP->CalculWindowAmbRetallat();
        this->camPrimeraP->AjustaAspectRatioWd();
        this->camPrimeraP->CalculaMatriuProjection();
        //this->camPrimeraP->setProjectionToGPU();
    }
}

void Escena::setDCamera(bool camGeneral, float d){
    if(camGeneral) {
        this->camGeneral->piram.d = d;

    }
    else {
        this->camPrimeraP->piram.d = d;
        this->camPrimeraP->CalculaMatriuProjection();
    }
}
