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
OUT vec2 v_texcoord;

OUT vec3 pos;
OUT vec3 Light1;
OUT vec3 Light2;
OUT vec3 Light3;
OUT vec3 N;
OUT float dist1;
OUT float dist2;
OUT float dist3;

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


void main()
{
  gl_Position = projection * model_view * vPosition;
  //gl_Position = gl_Position/gl_Position.w;
  gl_Position[3] = 1.0;

  pos = (model_view * vPosition).xyz;
  Light1 = normalize( (model_view * llum1.gpuPosicioLlum).xyz - pos );
  Light2 = normalize( (model_view * llum2.gpuPosicioLlum).xyz - pos );
  Light3 = normalize( (model_view * llum3.gpuPosicioLlum).xyz - pos );
  N = normalize( model_view * vec4(vNormal, 0.0) ).xyz;

  dist1 = length(llum1.gpuPosicioLlum - vPosition);
  dist2 = length(llum2.gpuPosicioLlum - vPosition);
  dist3 = length(llum3.gpuPosicioLlum - vPosition);

  v_texcoord = vCoordTexture;

}
