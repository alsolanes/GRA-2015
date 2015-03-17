#include "bola.h"
#include "math.h"

Bola::Bola() : Objecte(NumVertices)
{
    tethraedron(7);

}

Bola::~Bola()
{

}
void Bola::triangle( const point4& a, const point4& b, const point4& c )
{
    points[Index] = a;
    colors[Index] = vec4( vec3( 1.0, 1.0, 1.0 ), 1.0);
    Index++;
    points[Index] = b;
    colors[Index] = vec4( vec3( 1.0, 1.0, 1.0 ), 1.0);
    Index++;
    points[Index] = c;
    colors[Index] = vec4( vec3( 1.0, 1.0, 1.0 ), 1.0);
    Index++;
}

void Bola::tethraedron(int n)
{
    divide_triangle( v[0], v[1], v[2], n);
    divide_triangle( v[3], v[2], v[1], n);
    divide_triangle( v[0], v[3], v[1], n);
    divide_triangle( v[0], v[2], v[3], n);
}


void Bola::divide_triangle(point4 &a, point4 &b, point4 &c, int n)
{
    point4 v1, v2, v3;
    if (n>0)
    {
        v1 = calculVectorUnitari( a + b );
        v2 = calculVectorUnitari( a + c );
        v3 = calculVectorUnitari( b + c );
        divide_triangle(a, v2, v1, n-1);
        divide_triangle(c, v3, v2, n-1);
        divide_triangle(b, v1, v3, n-1);
        divide_triangle(v1, v2, v3, n-1);
    } else{
        triangle(a,b,c);
    }
}

vec4 Bola::calculVectorUnitari(const vec4& v)
{
    double modul;

    modul = sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
    vec4 out;
    out.x = v.x/modul;
    out.y = v.y/modul;
    out.z = v.z/modul;
    out.w = 1.0;

    return out;
}

