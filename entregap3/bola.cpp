#include "bola.h"

Bola::Bola(double x, double y, double z, QString tipoShading) : Objecte(NumVertices)//constructor de la bola blanca
{
    this->nomShading = tipoShading;
    vec4 componentAmbient = vec4(0.35, 0.3, 0.15, 1);
    vec4 componentDifusa = vec4(1.0, 0.8, 0.7, 1);
    vec4 componentEspecular = vec4(0.3, 0.4, 0.4, 1);
    float coeficient_reflex_especular = 0.1*100;
    mat = new Material(componentAmbient, componentDifusa, componentEspecular, coeficient_reflex_especular);


    xorig = yorig = zorig = 0;

    xRot = yRot = zRot = 0;

    vertexsTextura = new vec2[NumVertices];
    this->texture_path = "://resources/Bola0.jpg";

    make();

    aplicaTG(Translate(x,y,z)*Scale(0.025,0.025,0.025));
    capsa = calculCapsa3D();
}

Bola::Bola(double x, double y, double z, const QString &texturePath, QString tipoShading) : Objecte(NumVertices)
{
    this->nomShading = tipoShading;
    vec4 componentAmbient = vec4(0.35, 0.3, 0.15, 1);
    vec4 componentDifusa = vec4(1.0, 0.8, 0.829, 1);
    vec4 componentEspecular = vec4(0.296648, 0.4, 0.4, 1);
    float coeficient_reflex_especular = 0.1*128;
    mat = new Material(componentAmbient, componentDifusa, componentEspecular, coeficient_reflex_especular);

    xorig = yorig = zorig = 0;

    xRot = yRot = zRot = 0;

    vertexsTextura = new vec2[NumVertices];
    this->texture_path = texturePath;

    make();

    aplicaTGCentrat(RotateY(90) * RotateZ(-90)); // per mostrar el número a la part superior
    aplicaTG(Translate(x,y,z)*Scale(0.025,0.025,0.025));
    capsa = calculCapsa3D();
}

Bola::~Bola()
{
}


vec2 Bola::coordText(const point4 &c)
{
    float x = c.x; float y = c.y; float z = c.z;
    vec2 tmp;
    tmp = vec2(0.5 + atan2(z, x) / (2 * M_PI), 0.5 - asin(y) / M_PI);

    if (tmp.x < 0) tmp.x = 0;
    else if (tmp.x > 1) tmp.x = 1;

    if (tmp.y < 0) tmp.y = 0;
    else if (tmp.y > 1) tmp.y = 1;

    return tmp;
}

void Bola::triangle( const point4& a, const point4& b, const point4& c ){

    normaLight3 n = cross(a-b,b-c);

    points[Index] = a;
    //colors[Index] = color4(1.0, 1.0, 1.0, 1.0);
    vertexsTextura[Index] = coordText(-a);//invertim les coordenades ja que sino ens mostrava l'altra cara de la textura
    if(this->nomShading=="Flat")
        normal[Index] = n;
    else
        normal[Index] = vec3(a.x,a.y,a.z);
    Index++;

    points[Index] = b;
    //colors[Index] = color4(1.0, 1.0, 1.0, 1.0);
    vertexsTextura[Index] = coordText(-b);
    if(this->nomShading=="Flat")
        normal[Index] = n;
    else
        normal[Index] = vec3(b.x,b.y,b.z);
    Index++;

    points[Index] = c;
    //colors[Index] = color4(1.0, 1.0, 1.0, 1.0);
    vertexsTextura[Index] = coordText(-c);
    if(this->nomShading=="Flat")
        normal[Index] = n;
    else
        normal[Index] = vec3(c.x,c.y,c.z);
    Index++;
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

    this->tethraedron(4);
    init_textura();
}
