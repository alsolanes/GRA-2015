#include "bola.h"
#include "math.h"

Bola::Bola() : Objecte(NumVertices) //constructor de la bola blanca
{

    xorig = 0;
    yorig = 0;
    zorig = 0;

    xRot = 0;
    yRot = 0;
    zRot = 0;

    vertexsTextura = new vec2[NumVertices];
    this->texture_route="://resources/Bola0.jpg";

    make();

    capsa = calculCapsa3D();
}

Bola::Bola(const QString &texture_route) : Objecte(NumVertices) //constructor per la resta de boles
{

    xorig = 0;
    yorig = 0;
    zorig = 0;

    xRot = 0;
    yRot = 0;
    zRot = 0;

    vertexsTextura = new vec2[NumVertices];
    this->texture_route = texture_route;
    make();

    capsa = calculCapsa3D();
}

Bola::~Bola()
{

}
void Bola::triangle( const point4& a, const point4& b, const point4& c )
{
    points[Index] = a;
    colors[Index] = color4(1.0, 1.0, 1.0, 1.0);
    vertexsTextura[Index] = coordText(a);
    Index++;
    points[Index] = b;
    colors[Index] = color4(1.0, 1.0, 1.0, 1.0);
    vertexsTextura[Index] = coordText(b);
    Index++;
    points[Index] = c;
    colors[Index] = color4(1.0, 1.0, 1.0, 1.0);
    vertexsTextura[Index] = coordText(c);
    Index++;
}

vec2 Bola::coordText(const point4 &c)
{
    double u, v;
    u = 0.5 + (atan2(c.z, c.x) / 2 * M_PI);
    v = 0.5 - (asin(c.y) / M_PI);

    if (u < 0) u = 0;
    else if (u > 1) u = 1;

    if (v < 0) v = 0;
    else if (v > 1) v = 1;

    return vec2(u,v);
}

void Bola::tethraedron(int n)
{
    point4 v[4] = {
        vec4( 0.0, 0.0, 1.0, 1.0 ),
        vec4( 0.0, 0.942809, -0.333333, 1.0 ),
        vec4( -0.816497, -0.471405, -0.333333, 1.0 ),
        vec4( 0.816497, -0.471405, -0.333333, 1.0 )
    };
    divide_triangle( v[0], v[1], v[2], n);
    divide_triangle( v[3], v[2], v[1], n);
    divide_triangle( v[0], v[3], v[1], n);
    divide_triangle( v[0], v[2], v[3], n);
}


void Bola::divide_triangle(const point4 &a,const point4 &b,const point4 &c, int n)
{
    point4 v1, v2, v3;
    if (n>0)
    {
        v1 = calculVectorUnitari( a + b );
        v2 = calculVectorUnitari( a + c );
        v3 = calculVectorUnitari( b + c );
        divide_triangle(a, v1, v2, n-1);
        divide_triangle(c, v2, v3, n-1);
        divide_triangle(b, v3, v1, n-1);
        divide_triangle(v1, v3, v2, n-1);
    } else{
        triangle(a,b,c);
    }
}

vec4 Bola::calculVectorUnitari(const vec4& v)
{
    float suma = v.x*v.x+v.y*v.y+v.z*v.z;
    point4 sortida;
    if(suma>DivideByZeroTolerance){
        sortida = v/sqrt(suma);
        sortida.w = 1.0;
    }
    return sortida;
}

void Bola::make(){
    Index = 0;

    this->tethraedron(5);
    init_textura();
}

