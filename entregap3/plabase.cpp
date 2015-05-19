#include "plabase.h"

PlaBase::PlaBase() : Objecte(NumVertices)
{

    Index = 0;
    //cout << "Pla Base::Constructor" << endl;
    vertices[0] = point4( 0.5441, 0.0, 1.0, 1.0 );
    vertices[1] = point4( 0.5441, 0.0,-1.0, 1.0 );
    vertices[2] = point4(-0.5441, 0.0,-1.0, 1.0 );
    vertices[3] = point4(-0.5441, 0.0, 1.0, 1.0 );

    vertex_colors[0] = color4( 1.0, 0.0, 0.0, 1.0 );
    vertex_colors[1] = color4( 0.0, 1.0, 0.0, 1.0 );
    vertex_colors[2] = color4( 0.0, 0.0, 1.0, 1.0 );
    vertex_colors[3] = color4( 1.0, 1.0, 0.0, 1.0 );
    vertexsTextura = new vec2[NumVertices];
    this->texture_path = QString("://resources/Fabric_Green_L.jpg");


    vec3 ka = vec3(0.0, 0.05, 0.0);
    vec3 kd = vec3(0.4, 0.5, 0.4);
    vec3 ke = vec3(0.04, 0.7, 0.04);
    float kre = 0.078125 * 128;
    mat = new Material(ka, kd, ke, kre);


    make();
    capsa = calculCapsa3D();
}

PlaBase::~PlaBase()
{

}

void PlaBase::make()
{
    Index = 0;
    quad( 3, 0, 1, 2 );//llamando en este orden los triangulos se definen counterclok wise
    initTextura();
}

// quad generates two triangles for each face and assigns colors
//    to the vertices

void PlaBase::quad( int a, int b, int c, int d )
{
    normal3 n = cross(vertices[a] - vertices[b],vertices[b] - vertices[c]); //normal para cualquier shading

    points[Index] = vertices[a]; vertexsTextura[Index] = vec2(1.0, 0.0);  normal[Index] = n; Index++;
    points[Index] = vertices[b]; vertexsTextura[Index] = vec2(0.0, 0.0);  normal[Index] = n; Index++;
    points[Index] = vertices[c]; vertexsTextura[Index] = vec2(0.0, 1.0);  normal[Index] = n; Index++;

    n = cross(vertices[a] - vertices[c],vertices[c] - vertices[d]); //normal para cualquier shading

    points[Index] = vertices[a]; vertexsTextura[Index] = vec2(1.0, 0.0);  normal[Index] = n; Index++;
    points[Index] = vertices[c]; vertexsTextura[Index] = vec2(0.0, 1.0);  normal[Index] = n; Index++;
    points[Index] = vertices[d]; vertexsTextura[Index] = vec2(1.0, 1.0);  normal[Index] = n; Index++;
}

void PlaBase::initTextura()
 {
     //qDebug() << "Initializing textures...";

     // Carregar la textura
     glActiveTexture(GL_TEXTURE0);
     texture = new QOpenGLTexture(QImage("://resources/Fabric_Green_L.jpg"));
     texture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
     texture->setMagnificationFilter(QOpenGLTexture::Linear);

     texture->bind(0);

 }

vec3 PlaBase::vectorVertical(){
    vec4 d = points[1]/points[1].w - points[0]/points[0].w;
    return normalize(vec3(d.x, d.y, d.z));
}

vec3 PlaBase::vectorHoritzontal(){
    vec4 d = points[2]/points[2].w - points[1]/points[1].w;
    return normalize(vec3(d.x, d.y, d.z));
}

