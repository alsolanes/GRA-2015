#ifndef BOLA_H
#define BOLA_H

#include <objecte.h>

class Bola : public Objecte
{
public:
    Bola();
    ~Bola();

private:
    static const int NumVertices = 196608;
    point4 v[4] = {
        vec4( 0.0, 0.0, 1.0, 1.0 ),
        vec4( 0.0, 0.942809, -0.333333, 1.0 ),
        vec4( -0.816497, -0.471405, -0.333333, 1.0 ),
        vec4( 0.816497, -0.471405, -0.333333, 1.0 )
    };
    void triangle( const point4& a, const point4& b, const point4& c );
    void tethraedron(int n);
    void divide_triangle(point4 &a, point4 &b, point4 &c, int n);
    vec4 calculVectorUnitari(const vec4 &v);

};

#endif // BOLA_H
