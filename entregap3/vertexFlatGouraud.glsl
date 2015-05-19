#if __VERSION__<130
#define IN attribute
#define OUT varying
#else
#define IN in
#define OUT out
#endif


IN vec4 vPosition;
IN vec3 vNormal;
IN vec2 vCoordTexture;

OUT vec4 color;
OUT vec2 v_texcoord;

uniform mat4 model_view;
uniform mat4 projection;

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
uniform bool teTextura;

vec4 llum_1(){
    vec3 N = normalize( model_view*vec4(vNormal, 0.0) ).xyz;
    vec3 position = (model_view * vPosition).xyz;
    vec3 Light = normalize( (model_view * llum1.gpuPosicioLlum).xyz - position );
    vec3 H = normalize( Light + normalize( -position ) );
    float dist = length(llum1.gpuPosicioLlum - vPosition);
    vec4 cAmbient = llum1.gpuIntensitatAmbient * material.compA;
    vec4 cDifusa = llum1.gpuIntensitatDifusa * material.compD * max( dot(Light, N), 0.0 );
    vec4 cEspecular = max(pow(max(dot(N, H), 0.0), material.coefReflexEsp) * llum1.gpuIntensitatEspecular * material.compE , 0.0);
    float atenuacioDistancia = 1.0/(llum1.gpuAtenuacioConstant + llum1.gpuAtenuacioLineal * dist + llum1.gpuAtenuacioQuadratica * pow(dist,2.0) );
    return atenuacioDistancia * (cAmbient + cDifusa + cEspecular);
}

vec4 llum_2(){
    vec3 N = normalize( model_view*vec4(vNormal, 0.0) ).xyz;
    vec3 position = (model_view * vPosition).xyz;
    vec3 Light = normalize( (model_view * llum2.gpuPosicioLlum).xyz - position );
    vec3 H = normalize( Light + normalize( -position ) );
    float dist = length(llum2.gpuPosicioLlum - vPosition);
    vec4 cAmbient = llum2.gpuIntensitatAmbient * material.compA;
    vec4 cDifusa = llum2.gpuIntensitatDifusa * material.compD * max( dot(Light, N), 0.0 );
    vec4 cEspecular = max(pow(max(dot(N, H), 0.0), material.coefReflexEsp) * llum2.gpuIntensitatEspecular * material.compE , 0.0);
    float atenuacioDistancia = 1.0/(llum2.gpuAtenuacioConstant + llum2.gpuAtenuacioLineal * dist + llum1.gpuAtenuacioQuadratica * pow(dist,2.0) );
    return atenuacioDistancia * (cAmbient + cDifusa + cEspecular);
}

vec4 llum_3(){
    vec3 N = normalize( model_view*vec4(vNormal, 0.0) ).xyz;
    vec3 position = (model_view * vPosition).xyz;
    vec3 Light = normalize( (model_view * llum3.gpuPosicioLlum).xyz - position );
    vec3 H = normalize( Light + normalize( -position ) );
    float dist = length(llum3.gpuPosicioLlum - vPosition);
    vec4 cAmbient = llum3.gpuIntensitatAmbient * material.compA;
    vec4 cDifusa = llum3.gpuIntensitatDifusa * material.compD * max( dot(Light, N), 0.0 );
    vec4 cEspecular = max(pow(max(dot(N, H), 0.0), material.coefReflexEsp) * llum3.gpuIntensitatEspecular * material.compE , 0.0);
    float atenuacioDistancia = 1.0/(llum3.gpuAtenuacioConstant + llum3.gpuAtenuacioLineal * dist + llum1.gpuAtenuacioQuadratica * pow(dist,2.0) );
    return atenuacioDistancia * (cAmbient + cDifusa + cEspecular);
}

//gestionem 3 llums alhora amb flatgouraud
void main()
{
  gl_Position = projection * model_view * vPosition;
  gl_Position[3] = 1.0;

  color = llum_1() + llum_2() + llum_3();
  color +=  llumAmbient * material.compA;
  color[3] = 1.0;
  v_texcoord = vCoordTexture;
}


