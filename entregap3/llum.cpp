#include "llum.h"
using namespace std;

Llum::Llum()
{
}

Llum::Llum(vec4 posicio,
           vec4 direccio,
           vec4 iAmbient, vec4 iDifusa, vec4 iEspecular,
           float angleObertura,
           float atenuacioConstant, float atenuacioLineal, float atenuacioQuadratica,
           bool activa){

    posicio_llum = posicio;
    direccio_llum = direccio;
    this->iAmbient = iAmbient;
    this->iDifusa = iDifusa;
    this->iEspecular = iEspecular;
    this->angleObertura = angleObertura;
    atenuacio_constant = atenuacioConstant;
    atenuacio_lineal = atenuacioLineal;
    atenuacio_quadratica = atenuacioQuadratica;
    isActive = activa;
}

Llum::~Llum()
{

}

void Llum::toGPU(QGLShaderProgram *program)
{

    gl_IdLlum.posicio = program->uniformLocation(nom + ".gpuLightPosition");
    gl_IdLlum.direccio = program->uniformLocation(nom + ".gpuLightDirection");
    gl_IdLlum.intensitatAmbient = program->uniformLocation(nom + ".gpuIa");
    gl_IdLlum.intensitatDifusa = program->uniformLocation(nom + ".gpuId");
    gl_IdLlum.intensitatEspecular = program->uniformLocation(nom + ".gpuIs");
    gl_IdLlum.angleObertura = program->uniformLocation(nom + ".gpuBeamAngle");
    gl_IdLlum.atenuacioConstant= program->uniformLocation(nom + ".gpuAtt_constant");
    gl_IdLlum.atenuacioLineal = program->uniformLocation(nom + ".gpuAtt_linear");
    gl_IdLlum.atenuacioQuadratica = program->uniformLocation(nom + ".gpuAtt_quadratic");

    glUniform4fv(gl_IdLlum.posicio, 1, posicio_llum);
    glUniform4fv(gl_IdLlum.direccio, 1, direccio_llum);
    glUniform4fv(gl_IdLlum.intensitatAmbient, 1, iAmbient);
    glUniform4fv(gl_IdLlum.intensitatDifusa, 1, iDifusa);
    glUniform4fv(gl_IdLlum.intensitatEspecular, 1, iEspecular);
    glUniform1f(gl_IdLlum.angleObertura, angleObertura);
    glUniform1f(gl_IdLlum.atenuacioConstant, atenuacio_constant);
    glUniform1f(gl_IdLlum.atenuacioLineal, atenuacio_lineal);
    glUniform1f(gl_IdLlum.atenuacioQuadratica, atenuacio_quadratica);
}


