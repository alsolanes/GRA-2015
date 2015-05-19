#ifndef MATERIAL_H
#define MATERIAL_H

#include <Common.h>
#include <math.h>
#include <QGLShaderProgram>

class Material
{
public:
    Material(vec4 compAmbient, vec4 compDifusa, vec4 compEspecular, float coefReflexioExpecular);
    ~Material();
    void toGPU(QGLShaderProgram *program);

    vec4 componentAmbient, componentDifusa, componentEspecular;
    float coeficientReflexioEspecular;

    struct
    {
        GLuint componentAmbient;
        GLuint componentDifusa;
        GLuint componentEspecular;
        GLuint coeficientReflexioEspecular;
    }gl_IdMaterial;
};



#endif // MATERIAL_H
