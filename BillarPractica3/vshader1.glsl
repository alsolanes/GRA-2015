#if __VERSION__<130
#define IN attribute
#define OUT varying
#else
#define IN in
#define OUT out
#endif

IN vec4 vPosition;
IN vec4 vColor;
IN vec2 vCoordTexture;

OUT vec4 color;
OUT vec2 v_texcoord;

uniform mat4 model_view;
uniform mat4 projection;

struct tipusLlum
{
 vec4 LightPosition;
 vec3 Ld;
 vec3 atenuacio;
 vec3 Idifusa;
 vec3 Iambient;
 vec3 Iespecular;

 float coef_a;
};

uniform tipusLlum light;


uniform vec3 ambientGlobal;


void main()
{
    gl_Position = projection*model_view*vPosition;
    gl_Position /= gl_Position[3];
    //gl_Position = vPosition;
    color = vColor;
    // Pas de les coordenades de textura al fragment shader
    // El valor del color i les coordenades de textura s'interpolaran automaticament
    // en els fragments interiors a les cares dels polígons
    v_texcoord = vCoordTexture;
}
