
#include "Common.h"

point4 calculVectorUnitari( const vec4& v ){
    point4 v1 = normalize(v);
    vec3 vtmp (v1.x, v1.y, v1.z);
    vtmp = normalize(vtmp);
    v1 = point4 (vtmp.x, vtmp.y, vtmp.z, 1.0);
    return v1;
}
