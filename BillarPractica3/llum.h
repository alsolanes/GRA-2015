#ifndef LLUM_H
#define LLUM_H

#include <GL/gl.h>
#include <QGLShaderProgram>
#include <QObject>
#include <vector>
#include <Common.h>
#include <iostream>


class Llum
{
    struct {
     GLuint posicio;
     GLuint direccio;
     GLuint atenuacio;
     GLuint Idifusa;
     GLuint Iambient;
     GLuint Iespecular;
     GLuint a;
     } gl_IdLlum;

public:
    Llum();
    void toGPU(QGLShaderProgram *program);

    vec4 posicio;
    vec3 ld;
    vec3 Idifusa;
    vec3 Iespecular;
    vec3 Iambient;
    vec3 atenuacio;
    vec3 direccio;

    float a;


    ~Llum();
};

#endif // LLUM_H
