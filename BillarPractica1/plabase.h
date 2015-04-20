#ifndef PLABASE_H
#define PLABASE_H
#include <objecte.h>



class PlaBase : public Objecte
{
public:
    PlaBase();
    void make();
    void quad(int a, int b, int c, int d);
    ~PlaBase();

private:
    static const int NumVertices = 6;
    int a;
    int p;

    point4 vertices[4];
    color4 vertex_colors[4];


};

#endif // PLABASE_H
