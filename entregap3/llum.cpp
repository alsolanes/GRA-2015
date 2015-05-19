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

    gl_IdLlum.posicio = program->uniformLocation(nom + ".gpuPosicioLlum");
    gl_IdLlum.direccio = program->uniformLocation(nom + ".gpuDireccioLlum");
    gl_IdLlum.intensitatAmbient = program->uniformLocation(nom + ".gpuIntensitatAmbient");
    gl_IdLlum.intensitatDifusa = program->uniformLocation(nom + ".gpuIntensitatDifusa");
    gl_IdLlum.intensitatEspecular = program->uniformLocation(nom + ".gpuIntensitatEspecular");
    gl_IdLlum.angleObertura = program->uniformLocation(nom + ".gpuAngleObertura");
    gl_IdLlum.atenuacioConstant= program->uniformLocation(nom + ".gpuAtenuacioConstant");
    gl_IdLlum.atenuacioLineal = program->uniformLocation(nom + ".gpuAtenuacioLineal");
    gl_IdLlum.atenuacioQuadratica = program->uniformLocation(nom + ".gpuAtenuacioQuadratica");

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


