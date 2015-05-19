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

OUT vec3 Normal;
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
uniform bool teTextura;


void main()
{
  gl_Position = projection * model_view * vPosition;
  gl_Position[3] = 1.0;

  Normal = normalize(vNormal);
  v_texcoord = vCoordTexture;

}
