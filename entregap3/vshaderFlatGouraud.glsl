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
    vec4 cA;
    vec4 cD;
    vec4 cS;
    float coefRefEsp;
};

uniform tipusMaterial material;
uniform bool teTextura;

// 3 luces
void main()
{
  gl_Position = projection * model_view * vPosition;
  //gl_Position = gl_Position/gl_Position.w;
  gl_Position[3] = 1.0;

  vec3 pos = (model_view * vPosition).xyz;
  vec3 Light1 = normalize( (model_view * llum1.gpuPosicioLlum).xyz - pos );
  vec3 Light2 = normalize( (model_view * llum2.gpuPosicioLlum).xyz - pos );
  vec3 Light3 = normalize( (model_view * llum3.gpuPosicioLlum).xyz - pos );
  vec3 E = normalize( -pos );//vector de la pos al eye. en coordenadas de camara el eye esta en el origen
  vec3 H1 = normalize( Light1 + E );
  vec3 H2 = normalize( Light2 + E );
  vec3 H3 = normalize( Light3 + E );
  vec3 N = normalize( model_view*vec4(vNormal, 0.0) ).xyz;
  float dist1 = length(llum1.gpuPosicioLlum - vPosition);
  float dist2 = length(llum2.gpuPosicioLlum - vPosition);
  float distance3 = length(llum3.gpuPosicioLlum - vPosition);

  vec4 ambient1 = llum1.gpuIntensitatAmbient * material.cA;
  vec4 diffuse1 = llum1.gpuIntensitatDifusa * material.cD * max( dot(Light1, N), 0.0 );
  vec4 specular1 = max(pow(max(dot(N, H1), 0.0), material.coefRefEsp) * llum1.gpuIntensitatEspecular * material.cS , 0.0);
  float attDist1 = 1.0/(llum1.gpuAtenuacioConstant + llum1.gpuAtenuacioLineal * dist1 + llum1.gpuAtenuacioQuadratica * pow(dist1,2.0) );
  vec4 Ilum1 = attDist1 * (ambient1 + diffuse1 + specular1);

  vec4 ambient2 = llum2.gpuIntensitatAmbient * material.cA;
  vec4 diffuse2 = llum2.gpuIntensitatDifusa * material.cD * max( dot(Light2, N), 0.0 );
  vec4 specular2 = max(pow(max(dot(N, H2), 0.0), material.coefRefEsp) * llum2.gpuIntensitatEspecular * material.cS , 0.0);
  float attDist2 = 1.0/(llum2.gpuAtenuacioConstant + llum2.gpuAtenuacioLineal * dist2 + llum2.gpuAtenuacioQuadratica * pow(dist2,2.0) );
  vec4 Ilum2 = attDist2 * (ambient2 + diffuse2 + specular2);

  vec4 ambient3 = llum3.gpuIntensitatAmbient * material.cA;
  vec4 diffuse3 = llum3.gpuIntensitatDifusa * material.cD * max( dot(Light3, N), 0.0 );
  vec4 specular3 = max(pow(max(dot(N, H3), 0.0), material.coefRefEsp) * llum3.gpuIntensitatEspecular * material.cS , 0.0);
  float attDist3 = 1.0/(llum3.gpuAtenuacioConstant + llum3.gpuAtenuacioLineal * distance3 + llum3.gpuAtenuacioQuadratica * pow(distance3,2.0) );
  vec4 Ilum3 = attDist3 * (ambient3 + diffuse3 + specular3);

  color =  llumAmbient * material.cA  + Ilum1 + Ilum2 + Ilum3;
  color[3] = 1.0;
  v_texcoord = vCoordTexture;

}
