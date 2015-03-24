#ifndef PLABASE_H
#define PLABASE_H
#include <objecte.h>



class PlaBase : public Objecte
{
public:
    PlaBase();
    void make();
    ~PlaBase();

private:
    const int NumVertices = 6;
    int a;
    int p;

    point4 vertices[4];
    color4 vertex_colors[4];

    void quad(int a, int b, int c, int d);
};

#endif // PLABASE_H
