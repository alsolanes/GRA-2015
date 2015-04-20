#ifndef CONJUNTBOLES_H
#define CONJUNTBOLES_H

#include <bola.h>

#define QUANTITAT_BOLES 15

class ConjuntBoles : public Objecte
{
public:
    ConjuntBoles();
    ~ConjuntBoles();

    Bola *llista_boles[QUANTITAT_BOLES];
    vec4 *points_boles[QUANTITAT_BOLES];

    void aplicaTG(mat4 m);
    void aplicaTGCentrat(mat4 m);
    void draw();
    void toGPU(QGLShaderProgram *prog);
    Capsa3D calculCapsa3D();
    void toOrigin();
private:
    QString texture_routes[QUANTITAT_BOLES];


};

#endif // CONJUNTBOLES_H
