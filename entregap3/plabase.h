#ifndef PLABASE_H
#define PLABASE_H

#include <objecte.h>
#include <material.h>

const int NumVertices = 6; //(1 faces)*(2 triangles/face)*(3 vertices/triangle)

class PlaBase : public Objecte
{
public:
    PlaBase();
    virtual void make();
    ~PlaBase();

    vec3 vectorVertical();
    vec3 vectorHoritzontal();
private:
    int a; //amplada
    int p; //profunditat

    point4 vertices[4];
    color4 vertex_colors[4];

    void quad( int a, int b, int c, int d );
    void initTextura();
};

#endif // PLABASE_H
