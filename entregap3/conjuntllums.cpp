#include "conjuntllums.h"

ConjuntLlums::ConjuntLlums()
{
    vec4 pos = vec4(0.0, 0.1, 1.0, 1);
    vec4 dir = vec4(0.0, 0.1, 1.0 , 0);
    vec4 ia = vec4 (0.2, 0.2, 0.2, 1);
    vec4 id = vec4 (0.2, 0.1, 0.5, 1);
    vec4 is = vec4 (0.1, 0.1, 0.1, 1);
    float bAngle = 60.0;
    float atConst = 0.2;
    float atLin = 0.2;
    float atQuad = 0.2;
    bool on = true;
    PrimeraLlum = new Llum(pos, dir, ia, id, is, bAngle, atConst, atLin, atQuad, on);

    pos = vec4(2.0, 0.1, 1.0, 1);
    dir = vec4(2.0, 0.1, 1.0, 0);
    ia = vec4 (0.2, 0.2, 0.2, 1);
    id = vec4 (0.2, 0.1, 0.5, 1);
    is = vec4 (0.1, 0.1, 0.1, 1);
    bAngle = 60.0;
    atConst = 0.2;
    atLin = 0.2;
    atQuad = 0.2;
    on = true;
    SegonaLlum = new Llum(pos, dir, ia, id, is, bAngle, atConst, atLin, atQuad, on);

    pos = vec4(-2.0, 0.1, 1.0, 1);
    dir = vec4(-2.0, 0.1, 1.0, 0);
    ia = vec4 (0.2, 0.2, 0.2, 1);
    id = vec4 (0.2, 0.1, 0.5, 1);
    is = vec4 (0.1, 0.1, 0.1, 1);
    bAngle = 60.0;
    atConst = 0.2;
    atLin = 0.2;
    atQuad = 0.2;
    on = true;
    TerceraLlum = new Llum(pos, dir, ia, id, is, bAngle, atConst, atLin, atQuad, on);
}


void ConjuntLlums::toGPU(QGLShaderProgram *program)
{
     if(PrimeraLlum->isActive == true)//solo a la GPU si encendida
     {
        PrimeraLlum->nom = "light1";
        PrimeraLlum->toGPU(program);
     }
     if(SegonaLlum->isActive == true)
     {
        SegonaLlum->nom = "light2";
        SegonaLlum->toGPU(program);
     }
     if(TerceraLlum->isActive == true)
     {
        TerceraLlum->nom = "light3";
        TerceraLlum->toGPU(program);
     }
}

