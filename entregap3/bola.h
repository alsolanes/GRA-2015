#ifndef BOLA_H
#define BOLA_H


#include <objecte.h>

class Bola : public Objecte
{
public:
    Bola(double x, double y, double z, QString nomShading);
    Bola(double x, double y, double z, const QString &texture_path, QString nomShading);
    ~Bola();

private:
    static const int NumVertices = 15000;

    point4 vertices[4];
    color4 vertex_colors[4];

    void triangle( const point4& a, const point4& b, const point4& c );
    void tethraedron(int n);
    void divide_triangle(const point4 &a,const point4 &b,const point4 &c, int n);
    vec4 calculVectorUnitari(const vec4 &v);
    vec2 coordText(const point4 &c);
    void make();
    QString nomShading;
};

#endif // BOLA_H
