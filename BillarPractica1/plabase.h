#ifndef PLABASE_H
#define PLABASE_H
#include <objecte.h>

const int NumVertices = 6;

class PlaBase : public Objecte
{
public:
    PlaBase();
    virtual void make();
    ~PlaBase();
private:
    int a;
    int p;

    point4 vertices[4];
    color4 vertex_colors[4];

    void quad(int a, int b, int c, int d);
};

#endif // PLABASE_H
