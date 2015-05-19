#include "conjuntllums.h"

ConjuntLlums::ConjuntLlums()
{
    vec4 posAux = vec4(0.0, 0.1, 1.0, 1);
    vec4 dirAux = vec4(0.0, 0.1, 1.0 , 0);
    vec4 iambientAux = vec4 (0.2, 0.2, 0.2, 1);
    vec4 idifusaAux = vec4 (0.2, 0.1, 0.5, 1);
    vec4 iespecularAux = vec4 (0.1, 0.1, 0.1, 1);
    float angleAux = 60.0;
    float atenuacioCAux = 0.2;
    float atenuacioLAux = 0.2;
    float atenuacioQAux = 0.2;
    bool estaActivaAux = true;
    PrimeraLlum = new Llum(posAux,
                           dirAux,
                           iambientAux, idifusaAux, iespecularAux,
                           angleAux,
                           atenuacioCAux, atenuacioLAux, atenuacioQAux,
                           estaActivaAux);

    posAux = vec4(2.0, 0.1, 1.0, 1);
    dirAux = vec4(2.0, 0.1, 1.0, 0);
    iambientAux = vec4 (0.2, 0.2, 0.2, 1);
    idifusaAux = vec4 (0.2, 0.1, 0.5, 1);
    iespecularAux = vec4 (0.1, 0.1, 0.1, 1);
    angleAux = 60.0;
    atenuacioCAux = 0.2;
    atenuacioLAux = 0.2;
    atenuacioQAux = 0.2;
    estaActivaAux = true;
    SegonaLlum = new Llum(posAux,
                          dirAux,
                          iambientAux, idifusaAux, iespecularAux,
                          angleAux,
                          atenuacioCAux, atenuacioLAux, atenuacioQAux,
                          estaActivaAux);


    posAux = vec4(-2.0, 0.1, 1.0, 1);
    dirAux = vec4(-2.0, 0.1, 1.0, 0);
    iambientAux = vec4 (0.2, 0.2, 0.2, 1);
    idifusaAux = vec4 (0.2, 0.1, 0.5, 1);
    iespecularAux = vec4 (0.1, 0.1, 0.1, 1);
    angleAux = 60.0;
    atenuacioCAux = 0.2;
    atenuacioLAux = 0.2;
    atenuacioQAux = 0.2;
    estaActivaAux = true;
    TerceraLlum = new Llum(posAux,
                           dirAux,
                           iambientAux, idifusaAux, iespecularAux,
                           angleAux,
                           atenuacioCAux, atenuacioLAux, atenuacioQAux,
                           estaActivaAux);
}

//enviarem a la gpu les llums actives
void ConjuntLlums::toGPU(QGLShaderProgram *program)
{
     if(PrimeraLlum->isActive == true)
     {
        PrimeraLlum->nom = "llum1";
        PrimeraLlum->toGPU(program);
     }
     if(SegonaLlum->isActive == true)
     {
        SegonaLlum->nom = "llum2";
        SegonaLlum->toGPU(program);
     }
     if(TerceraLlum->isActive == true)
     {
        TerceraLlum->nom = "llum3";
        TerceraLlum->toGPU(program);
     }
}

