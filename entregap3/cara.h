#ifndef _CARA_H_
#define _CARA_H_

#include <vector>
#include <Common.h>

using namespace std;

typedef vec4 Vertices;
class Cara
{
 public:
    Cara();

    Cara(int i1, int i2, int i3, int i4=-1);

    vec4 color;
    vector<int> idxVertices;


    vec3 normal;
    void calculaNormal(vector<Vertices> &);
};



#endif
