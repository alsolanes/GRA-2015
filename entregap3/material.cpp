#include "material.h"


Material::Material(vec4 compAmbient, vec4 compDifusa, vec4 compEspecular, float coefReflexioExpecular)
{
    this->componentAmbient = compAmbient;
    this->componentDifusa = compDifusa;
    this->componentEspecular = compEspecular;
    this->coeficientReflexioEspecular = coefReflexioExpecular;
}

Material::~Material()
{

}

void Material::toGPU(QGLShaderProgram *program)
{
    gl_IdMaterial.componentAmbient = program->uniformLocation("material.cA");
    glUniform4fv(gl_IdMaterial.componentAmbient, 1, componentAmbient);

    gl_IdMaterial.componentDifusa = program->uniformLocation("material.cD");
    glUniform4fv(gl_IdMaterial.componentDifusa, 1, componentDifusa);

    gl_IdMaterial.componentEspecular = program->uniformLocation("material.cE");
    glUniform4fv(gl_IdMaterial.componentEspecular, 1, componentEspecular);

    gl_IdMaterial.coeficientReflexioEspecular = program->uniformLocation("material.coefRefEsp");
    glUniform1f(gl_IdMaterial.coeficientReflexioEspecular, coeficientReflexioEspecular);
}


