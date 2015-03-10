#ifndef BOLA_H
#define BOLA_H

#include <objecte.h>

class Bola : public Objecte
{
public:
    Bola();
    ~Bola();

private:
    point4 v[4] = {
        vec4( 0.0, 0.0, 1.0, 1.0 ),
        vec4( 0.0, 0.942809, -0.333333, 1.0 ),
        vec4( -0.816497, -0.471405, -0.333333, 1.0 ),
        vec4( 0.816497, -0.471405, -0.333333, 1.0 )
    };

    int a;
    int p;

};

#endif // BOLA_H
