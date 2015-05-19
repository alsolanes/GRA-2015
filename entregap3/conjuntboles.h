#ifndef CONJUNTBOLES_H
#define CONJUNTBOLES_H

#include <bola.h>

#define QUANTITAT_BOLES 15

class ConjuntBoles : public Objecte
{
public:
    ConjuntBoles(QString nomShading);
    ~ConjuntBoles();

    vector<Bola*> llista_boles;
    QString texture_routes[QUANTITAT_BOLES];
    const vec4 *points_boles[QUANTITAT_BOLES];

    void aplicaTG(mat4 m);
    void aplicaTGCentrat(mat4 m);
    void aplicaTGPoints(mat4 m);
    void draw();
    void toGPU(QGLShaderProgram *prog);

    void toOrigin();

    Capsa3D calculCapsa3D();
};

#endif // CONJUNTBOLES_H
