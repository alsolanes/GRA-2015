#if __VERSION__<130
#define IN varying
#define OUT varying
#else
#define IN in
#define OUT out
#endif

IN vec3 Normal;
IN vec2 v_texcoord;

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

uniform sampler2D texMap;
uniform bool teTextura;

void main()
{
    float intensity;
    vec4 color;

    intensity = dot(normalize(llum1.gpuPosicioLlum.xyz), Normal);

    if (intensity > 0.9)
        color = vec4(0.8, 1.0, 0.8, 1.0);
    else if (intensity > 0.6 && intensity <= 0.9)
        color = vec4(0.6, 0.7, 0.6, 1.0);
    else if (intensity > 0.3 && intensity <= 0.6)
        color = vec4(0.2, 0.5, 0.4, 1.0);
    else
        color = vec4(0.1, 0.3, 0.1, 1.0);
        
    if(teTextura){
        gl_FragColor = 0.25 * color + 0.75 * texture2D(texMap, v_texcoord);
    }else{
        gl_FragColor = color;
    }
}

