#if __VERSION__<130
#define IN varying
#define OUT varying
#else
#define IN in
#define OUT out
#endif

IN vec2 v_texcoord;

IN vec3 pos;
IN vec3 Light1;
IN vec3 Light2;
IN vec3 Light3;
IN vec3 N;
IN float dist1;
IN float dist2;
IN float dist3;

struct tipusLlum{
    vec4 gpuPosicioLlum;
    vec4 gpuDireccioLlum;
    vec4 gpuIntensitatAmbient;
    vec4 gpuIntensitatDifusa;
    vec4 gpuIntensitatEspecular;
    float gpuAngleObertura;
    float gpuAtenuacioConstant;
    float gpuAtenuacioLineal;
    float gpuAtenuacioQuadratica;
};

uniform tipusLlum llum1;
uniform tipusLlum llum2;
uniform tipusLlum llum3;
uniform vec4 llumAmbient;

struct tipusMaterial{
    vec4 compA;
    vec4 compD;
    vec4 compE;
    float coefReflexEsp;
};

uniform tipusMaterial material;


uniform sampler2D texMap;
uniform bool teTextura;

vec4 llum_1(){
    vec3 H = normalize( Light1 + normalize( -pos ) );
    vec4 ambient = llum1.gpuIntensitatAmbient * material.compA;
    vec4 diffuse = llum1.gpuIntensitatDifusa * material.compD * max( dot(Light1, N), 0.0 );
    vec4 specular = max(pow(max(dot(N, H), 0.0), material.coefReflexEsp) * llum1.gpuIntensitatEspecular * material.compE , 0.0);
    float attDist = 1.0/(llum1.gpuAtenuacioConstant + llum1.gpuAtenuacioLineal * dist1 + llum1.gpuAtenuacioQuadratica * pow(dist1,2.0) );
    return attDist * (ambient + diffuse + specular);
}
vec4 llum_2(){
    vec3 H = normalize( Light2 + normalize( -pos ) );
    vec4 ambient = llum2.gpuIntensitatAmbient * material.compA;
    vec4 diffuse = llum2.gpuIntensitatDifusa * material.compD * max( dot(Light2, N), 0.0 );
    vec4 specular = max(pow(max(dot(N, H), 0.0), material.coefReflexEsp) * llum2.gpuIntensitatEspecular * material.compE , 0.0);
    float attDist = 1.0/(llum2.gpuAtenuacioConstant + llum2.gpuAtenuacioLineal * dist2 + llum2.gpuAtenuacioQuadratica * pow(dist2,2.0) );
    return attDist * (ambient + diffuse + specular);
}

vec4 llum_3(){
    vec3 H = normalize( Light3 + normalize( -pos ) );
    vec4 ambient = llum3.gpuIntensitatAmbient * material.compA;
    vec4 diffuse = llum3.gpuIntensitatDifusa * material.compD * max( dot(Light3, N), 0.0 );
    vec4 specular = max(pow(max(dot(N, H), 0.0), material.coefReflexEsp) * llum3.gpuIntensitatEspecular * material.compE , 0.0);
    float attDist = 1.0/(llum3.gpuAtenuacioConstant + llum3.gpuAtenuacioLineal * dist3 + llum3.gpuAtenuacioQuadratica * pow(dist3,2.0) );
    return attDist * (ambient + diffuse + specular);
}

void main()
{
    vec4 color = llum_1() + llum_2() + llum_3();
    color +=  llumAmbient * material.compA;
    color[3] = 1.0;
    if(teTextura){
       gl_FragColor = 0.25 * color + 0.75 * texture2D(texMap, v_texcoord);
    }else{
       gl_FragColor = color;
    }
}

