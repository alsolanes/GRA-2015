#include "bola.h"

Bola::Bola() : Objecte(NumVertices)
{

}

Bola::~Bola()
{

}

void Bola::triangle( const point4& a, const point4& b, const point4& c )
{
    points[Index] = a;
    Index++;
    points[Index] = b;
    Index++;
    points[Index] = c;
    Index++;
}

void Bola::tethraedron(int n)
{
    divide_triangle( v[0], v[1], v[2], n);
    divide_triangle( v[3], v[2], v[1], n);
    divide_triangle( v[0], v[3], v[1], n);
    divide_triangle( v[0], v[2], v[3], n);
}

void divide_triange(point4 a, point4 b, point4 c, int n)
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
    }
}

point4 Bola::calculVectorUnitari(point4 v)
{
    int modul;
    modul = Math.sqrt(Math.Pow(v(0),2), Math.Pow(v(1),2), Math.Pow(v(2),2), Math.Pow(v(3),2));
    v(0) = v(0)/modul;
    v(1) = v(1)/modul;
    v(2) = v(2)/modul;
    v(3) = v(3)/modul;

    return v;
}
