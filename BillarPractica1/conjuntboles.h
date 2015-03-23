#ifndef CONJUNTBOLES_H
#define CONJUNTBOLES_H

#include <bola.h>

#define QUANTITAT_BOLES 15

class ConjuntBoles
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
private:

};

#endif // CONJUNTBOLES_H
