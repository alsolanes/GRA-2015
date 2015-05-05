#include "llum.h"

Llum::Llum()
{

}

Llum::~Llum()
{

}

void Llum::toGPU(QGLShaderProgram *program){
     gl_IdLlum.posicio = program->uniformLocation("light.LightPosition");
     gl_IdLlum.Idifusa = program->uniformLocation("light.Idifusa");
     gl_IdLlum.Iespecular = program->uniformLocation("light.Iespecular");
     gl_IdLlum.Iambient = program->uniformLocation("light.Iambient");
     gl_IdLlum.atenuacio = program->uniformLocation("light.atenuacio");
     gl_IdLlum.direccio = program->uniformLocation("light.Ld");
     gl_IdLlum.a = program->uniformLocation("light.coef_a");

     // Bind de les zones de memoria que corresponen a les variables de la CPU
     glUniform4fv(gl_IdLlum.posicio, 1, posicio); //posicioLlum és un vec4
     glUniform3fv(gl_IdLlum.Idifusa, 1, Idifusa); // difusa és un vec3
     glUniform3fv(gl_IdLlum.Iespecular, 1, Iespecular ); // especular és un vec3
     glUniform3fv(gl_IdLlum.Iambient, 1, Iambient ); // ambient és un vec3
     glUniform3fv(gl_IdLlum.atenuacio, 1, atenuacio ); // atenuacio és un vec3
     glUniform3fv(gl_IdLlum.direccio, 1, direccio ); // posicio és un vec3
     glUniform1f(gl_IdLlum.a, a); // coef_a és un Glfloat
}
