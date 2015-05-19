/***************************************************/
/*           Definicio de la camera                */
/***************************************************/
#ifndef CAMERA_INCLOS
#define CAMERA_INCLOS
#include <stdio.h>
#include <Common.h>
#include <QGLShaderProgram>

#define PI 3.14159

#define MAXDPOST 100000
#define MINDANT -100000
#define EPS 0.001

#define DEGREES *180.0/PI

typedef enum {VISTA_X = 0, VISTA_Y = 1, VISTA_Z = 2, AXONOMETRIC = 3} TipVista; 

typedef enum {YAMUNT = 0, YABAIX = 1} Orienty; 

typedef enum {PARALLELA = 0, PERSPECTIVA = 1} TipProj; 


typedef struct
 {
  double      angy, angx, angz;  /* angles de gir del sistema de coords obser */
  vec4        vrp;               /* view reference point */
  vec4        obs;               /* posicio de l'observador */
  vec4        vup;               /* verticalitat de la càmera */
 } VisuSystem;

typedef struct  
 {
  TipProj    proj;           /* tipus de proj: 0 paral.lela 1 perspectiva */
  double     d;              /* distancia observador a pla de projeccio */
  double     dant, dpost;    /* distancies al pla de retallat anterior i posterior desde l'observador*/
  double     alfav, alfah;   /* angles d'obertura camera vertical i horitzontal */
} PiramProj;

/* =================================== */
/* =                                 = */
/* =             Camera              = */
/* =                                 = */
/* =================================== */

class Camera
{
public:
    explicit Camera();
    ~Camera() {}

    //passem el program a ini per mantenir el parametre program
    void ini(int a, int h, Capsa3D c,QGLShaderProgram *program);

    void CalculaMatriuModelView();
    void CalculaMatriuProjection();
    void CalculWindow(Capsa3D);
    void CalculWindowAmbRetallat();

    vec4 CalculObs(vec4 vrp, double d, double angx, double angy);
    vec3 CalculVup(double angx, double angy, double angz);

    void CreaMatDp(mat4 &MDP); //crea la matriu de deformació
    void AjustaAspectRatioWd();
    void AmpliaWindow(double r);
    void CalculAngleOberturaVertical();
    void CalculAngleOberturaHoritzontal();

    Capsa2D  CapsaMinCont2DXYVert( vec4 *v, int nv);

    void setViewport(int x, int y, int a, int h);
    //s'ha tret el program perque l'hem definit com a parametre i aixi evitem anar-lo passant
    //definim el program al fer l'ini
    //hem tret el paràmetre mat4 que rebien els setModelView i setProjection ja que envien les matrius modView i proj
    void setProjectionToGPU(QGLShaderProgram *prog, mat4 p);
    void setModelViewToGPU(QGLShaderProgram *prog, mat4 p);
    void toGPU(QGLShaderProgram *program);

    void defineAngles(float angX, float angY, float angZ);
    void rotate(Capsa3D c);
    void pan(int dx, int dy);
    void zoom(int positiu);


    VisuSystem vs;      /* Sistema de visualitzacio  */
    PiramProj piram;    /* Piramide de visualitzacio */
    Capsa2D wd;	      /* Window                    */
    Capsa2D vp;       /* Viewport                  */
    Capsa3D capsaEscena;
private:
    void VertexCapsa3D(Capsa3D capsaMinima, vec4 vaux[8]);

    mat4  modView; // Matriu model-view de la CPU
    mat4  proj;  // Matriu projection de la CPU
    GLuint  model_view;  // model-view matrix uniform shader variable (GPU)
    GLuint  projection;  // projection matrix uniform shader variable (GPU)
    QGLShaderProgram *prog; // program afegit per evitar anar-lo enviant cada vegada


};


#endif








