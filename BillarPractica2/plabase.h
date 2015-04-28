#ifndef PLABASE_H
#define PLABASE_H

#include <objecte.h>
#include <QGLShaderProgram>
#include <QOpenGLTexture>

class PlaBase : public Objecte
{
public:
    PlaBase();
    ~PlaBase();
    void make();
    void quad( int a, int b, int c, int d );

    vec3 vectorVertical();
    vec3 vectorHoritzontal();

private:
    int a, p;
    static const int NumVertices = 12; //6 pel pla superior i 6 per l'inferior

    point4 vertices[4];
    color4 vertex_colors[4];


};

#endif // PLABASE_H
