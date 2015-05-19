#include "escena.h"

Escena::Escena(int vpa, int vph)
{
    capsaMinima.pmin[0] = 0.0; capsaMinima.pmin[1] = 0.0; capsaMinima.pmin[2]=0.0;
    capsaMinima.a = 1; capsaMinima.h = 1; capsaMinima.p = 1;

    taulaBillar = NULL;
    plaBase = NULL;
    bola = NULL;
    conjuntBoles = NULL;

    iniCamera(true, vpa, vph);

    llumAmbient = vec4(0.4, 0.4, 0.4, 1.0);
    conjuntLlums = new ConjuntLlums();

}

Escena::~Escena()
{
    if (taulaBillar!=NULL)
       delete this->taulaBillar;
    if (plaBase!=NULL)
       delete this->plaBase;
    if (bola!=NULL)
       delete this->bola;
    if (conjuntBoles!=NULL)
       delete this->conjuntBoles;
}

void Escena::iniCamera(bool camGen, int a, int h){
    if(camGen == true){
       camGeneral.piram.proj = PARALLELA;
       camGeneral.ini(a, h, capsaMinima);

       camGeneral.vs.obs = vec4(0.0, 20.0, 0.0, 1.0);     
       point4 vrp = point4(0.0, 0.0, 0.0, 1.0);
       setVRPCamera(true, vrp);
       setDCamera(true, 20.0);
       setAnglesCamera(true, -90.0, 0.0, 0.0);

       camGeneral.CalculWindow(capsaMinima);       
       camGeneral.piram.dant = 0.1;
       camGeneral.piram.dpost = 30.0;
       camGeneral.CalculaMatriuProjection();
   }else{

   }
}

void Escena::setAnglesCamera(bool camGen, float angX, float angY, float angZ){
    if(camGen == true){
        camGeneral.vs.angx = angX;
        camGeneral.vs.angy = angY;
        camGeneral.vs.angz = angZ;
        vec3 vu = camGeneral.CalculVup(camGeneral.vs.angx, camGeneral.vs.angy, camGeneral.vs.angz);
        camGeneral.vs.vup = vec4(vu[0], vu[1], vu[2], 0.0);
        camGeneral.vs.obs = camGeneral.CalculObs(camGeneral.vs.vrp, camGeneral.piram.d, camGeneral.vs.angx, camGeneral.vs.angy);
        camGeneral.CalculaMatriuModelView();
    }else{
    }
}

void Escena::setVRPCamera(bool camGen, point4 vrp){
    if(camGen == true){
         camGeneral.vs.vrp = vrp;
         camGeneral.vs.angx = 180.0 /M_PI * atan2(vrp.y-camGeneral.vs.obs.y, vrp.z-camGeneral.vs.obs.z);
         camGeneral.vs.angy = 180.0 /M_PI * atan2(camGeneral.vs.obs.x - vrp.x, camGeneral.vs.obs.z - vrp.z);
         camGeneral.vs.angz = 180.0 /M_PI * atan2(vrp.y-camGeneral.vs.obs.y, vrp.x-camGeneral.vs.obs.x);
         camGeneral.CalculaMatriuModelView();
     }else{
     }
}

void Escena::setWindowCamera(bool camGen, bool retallat, Capsa2D window){
    if(camGen == true){        
        if(retallat == true){
            camGeneral.wd = window;
            camGeneral.CalculWindowAmbRetallat();
        }
        camGeneral.AjustaAspectRatioWd();
        camGeneral.CalculaMatriuProjection();
    }else{
    }
}

void Escena::setDCamera(bool camGen, float d){
    if(camGen == true){
        camGeneral.piram.d = d;
        camGeneral.CalculObs(camGeneral.vs.vrp, d, camGeneral.vs.angx, camGeneral.vs.angy);
        camGeneral.CalculaMatriuModelView();
    }else{
    }
}

void Escena::addObjecte(Objecte *obj) {
    if (dynamic_cast<TaulaBillar*>(obj)){
        this->taulaBillar = (TaulaBillar*)obj;
        llista_objectes.push_back(taulaBillar);
    } else if (dynamic_cast<PlaBase*>(obj)){
        this->plaBase = (PlaBase*)obj;
        llista_objectes.push_back(plaBase);
    }else if (dynamic_cast<Bola*>(obj)){
        this->bola= (Bola*)obj;
        llista_objectes.push_back(bola);
    }else if(dynamic_cast<ConjuntBoles*>(obj) && conjuntBoles ==NULL){
        this->conjuntBoles = (ConjuntBoles*)obj;
        llista_objectes.push_back(conjuntBoles);
    }
    CapsaMinCont3DEscena();
}


void Escena::CapsaMinCont3DEscena()
{
    // Metode a implementar
    Capsa3D capsaAux;
    vec3 pmax;

    capsaMinima.pmin[0]=INFINITY;
    capsaMinima.pmin[1]=INFINITY;
    capsaMinima.pmin[2]=INFINITY;
    pmax[0] = -INFINITY;
    pmax[1] = -INFINITY;
    pmax[2] = -INFINITY;

    for (int i=0; i<llista_objectes.size(); i++) {
        capsaAux = llista_objectes[i]->calculCapsa3D();

        if (capsaMinima.pmin[0]>capsaAux.pmin[0])
            capsaMinima.pmin[0] = capsaAux.pmin[0];
        if (pmax[0]<capsaAux.pmin[0]+capsaAux.a)
            pmax[0] = capsaAux.pmin[0]+capsaAux.a;
        if (capsaMinima.pmin[1]>capsaAux.pmin[1])
            capsaMinima.pmin[1] = capsaAux.pmin[1];
        if (pmax[1]<capsaAux.pmin[1]+capsaAux.h)
            pmax[1] = capsaAux.pmin[1]+capsaAux.h;
        if (capsaMinima.pmin[2]>capsaAux.pmin[2])
            capsaMinima.pmin[2] = capsaAux.pmin[2];
        if (pmax[2]<capsaAux.pmin[2]+capsaAux.p)
            pmax[2] = capsaAux.pmin[2]+capsaAux.p;
    }
    capsaMinima.a = pmax[0]-capsaMinima.pmin[0];
    capsaMinima.h = pmax[1]-capsaMinima.pmin[1];
    capsaMinima.p = pmax[2]-capsaMinima.pmin[2];
    capsaMinima.centre = capsaMinima.pmin + vec3(capsaMinima.a/2, capsaMinima.h/2, capsaMinima.p/2);
}

void Escena::aplicaTG(mat4 m) {

    for(unsigned int i=0;i<QUANTITAT_BOLES;i++)
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
    for(unsigned int i = 0; i < QUANTITAT_BOLES; i++)
        llista_objectes[i]->aplicaTGCentrat(mRes);
    //recalculem la capsa
    CapsaMinCont3DEscena();
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
            vecMoviment = normalize(vec3(0,0,1));
        break;
    case 2: //down
        if(cameraGeneral)
            vecMoviment = -plaBase->vectorVertical();
        else
            vecMoviment = -normalize(vec3(0,0,1));
        break;
    case 3: //left
        if(cameraGeneral)
            vecMoviment = plaBase->vectorHoritzontal();
        else{
            vecMoviment = normalize(vec3(1,0,0));
        }
        break;
    case 4: //right
        if(cameraGeneral)
            vecMoviment = -plaBase->vectorHoritzontal();
        else{
            vecMoviment = normalize(vec3(-1,0,0));
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

void Escena::draw(bool cameraActual) {
    if (taulaBillar!=NULL){
        taulaBillar->toGPU(pr);

        setAmbientToGPU(pr);
        conjuntLlums->toGPU(pr);

        setLlumiTexturaToGPU(pr, teTextura);

        camGeneral.toGPU(pr);
        taulaBillar->draw();
    }

    if (plaBase!=NULL){
        plaBase->texture->bind(0);
        plaBase->toGPU(pr);

        setAmbientToGPU(pr);
        conjuntLlums->toGPU(pr);

        setLlumiTexturaToGPU(pr, teTextura);

        camGeneral.toGPU(pr);
        plaBase->draw();
    }

    if (bola!=NULL){
        bola->texture->bind(0);
        bola->toGPU(pr);

        setAmbientToGPU(pr);
        conjuntLlums->toGPU(pr);

        setLlumiTexturaToGPU(pr, teTextura);

        camGeneral.toGPU(pr);
        bola->draw();
    }

    if (conjuntBoles!=NULL){
        for (int i=0; i<QUANTITAT_BOLES; i++) {
            conjuntBoles->llista_boles[i]->texture->bind(0);
            conjuntBoles->llista_boles[i]->toGPU(pr);

            setAmbientToGPU(pr);
            conjuntLlums->toGPU(pr);

            setLlumiTexturaToGPU(pr, teTextura);

            camGeneral.toGPU(pr);
            conjuntBoles->llista_boles[i]->draw();
        }
    }
}


void Escena::setAmbientToGPU(QGLShaderProgram *program){
    GLuint LuzAmbLocation = program->uniformLocation("llumAmbient");
    glUniform4fv(LuzAmbLocation, 1, llumAmbient);
}

void Escena::setLlumiTexturaToGPU(QGLShaderProgram *program, bool conText)
{
    GLuint conTextLocation = program->uniformLocation("teTextura");
    glUniform1f( conTextLocation, conText );
}



