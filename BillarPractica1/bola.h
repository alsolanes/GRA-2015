#ifndef BOLA_H
#define BOLA_H

#include <objecte.h>

class Bola : public Objecte
{
public:
    Bola();
    Bola(const QString &texture_route);
    ~Bola();

private:
    //NumVertices sera: 4 cares del tetraedre* 12 vertex cada cara * 4**iteracions
    static const int NumVertices = 1000000;
    color4 vertex_colors[4];

    void triangle( const point4& a, const point4& b, const point4& c );
    void tethraedron(int n);
    void divide_triangle(const point4 &a,const point4 &b,const point4 &c, int n);
    vec4 calculVectorUnitari(const vec4 &v);
    vec2 coordText(const point4 &c);
    void make();
};

#endif // BOLA_H
