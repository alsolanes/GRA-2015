#ifndef CONJUNTBOLES_H
#define CONJUNTBOLES_H

#include <bola.h>

#define QUANTITAT_BOLES 15

class ConjuntBoles : public Objecte
{
public:
    ConjuntBoles();
    ~ConjuntBoles();
    Capsa3D capsa;
    Bola *llista_boles[QUANTITAT_BOLES];


    void aplicaTG(mat4 m);
    void aplicaTGCentrat(mat4 m);
    void aplicaTGPoints(mat4 m);
    void draw();
    void toGPU(QGLShaderProgram *prog);

    void toOrigin();
private:
    QString texture_routes[QUANTITAT_BOLES];
    const vec4 *points_boles[QUANTITAT_BOLES];
    Capsa3D calculCapsa3D();

};

#endif // CONJUNTBOLES_H
