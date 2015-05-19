#ifndef LLUM_H
#define LLUM_H

#include <Common.h>
#include <QGLShaderProgram>

class Llum
{
public:
    Llum();
    Llum(vec4 posicio,
         vec4 direccio,
         vec4 intensitatAmbient, vec4 intensitatDifusa, vec4 intensitatEspecular,
         float angleObertura,
         float atenuacioConstant, float atenuacioLineal, float atenuacioQuadratica,
         bool activa);
    ~Llum();
    void toGPU(QGLShaderProgram *program);

    vec4 posicio_llum;
    vec4 direccio_llum;
    vec4 iAmbient, iDifusa, iEspecular;
    float angleObertura, atenuacio_constant, atenuacio_lineal, atenuacio_quadratica;
    bool isActive;
    QString nom;
    struct{
        GLuint posicio;
        GLuint direccio;
        GLuint intensitatAmbient,intensitatDifusa,intensitatEspecular;
        GLuint angleObertura;
        GLuint atenuacioConstant, atenuacioLineal, atenuacioQuadratica;
    }gl_IdLlum;
};

#endif // LLUM_H
