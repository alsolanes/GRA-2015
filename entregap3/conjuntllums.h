#ifndef CONJUNTLLUMS_H
#define CONJUNTLLUMS_H

#include <Common.h>
#include <llum.h>

class QGLShaderProgram;

class ConjuntLlums
{
public:
    ConjuntLlums();
    ~ConjuntLlums();
    void toGPU(QGLShaderProgram *program);
    // tindrem 3 llums
    Llum *PrimeraLlum, *SegonaLlum, *TerceraLlum;
};

#endif // CONJUNTLLUMS_H
