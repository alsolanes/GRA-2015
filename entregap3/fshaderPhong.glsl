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
    vec4 cA;
    vec4 cD;
    vec4 cS;
    float coefRefEsp;
};

uniform tipusMaterial material;


uniform sampler2D texMap;
uniform bool teTextura;

void main()
{
  
  vec3 E = normalize( -pos );//vector de la pos al eye. En coordenadas de camara el eye esta en el origen
  vec3 H1 = normalize( Light1 + E );
  vec3 H2 = normalize( Light2 + E );
  vec3 H3 = normalize( Light3 + E );
  
  

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
  float attDist3 = 1.0/(llum3.gpuAtenuacioConstant + llum3.gpuAtenuacioLineal * dist3 + llum3.gpuAtenuacioQuadratica * pow(dist3,2.0) );
  vec4 Ilum3 = attDist3 * (ambient3 + diffuse3 + specular3);

  vec4 color =  llumAmbient * material.cA  + Ilum1 + Ilum2 + Ilum3;
  color[3] = 1.0;

   if(teTextura){
       gl_FragColor = 0.25 * color + 0.75 * texture2D(texMap, v_texcoord);
   }else{
       gl_FragColor = color;
   }
}

