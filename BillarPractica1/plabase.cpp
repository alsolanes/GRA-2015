#include "plabase.h"

PlaBase::PlaBase() : Objecte(NumVertices)
{

    vertices[0] = point4( 1, 0, 1, 1.0 );//no es veu res perquè pla paral·lel a y
    vertices[3] = point4( 1, 0,-1, 1.0 );
    vertices[2] = point4(-1, 0,-1, 1.0 );
    vertices[1] = point4(-1, 0, 1, 1.0 );

    vertex_colors[0] = color4( 1.0, 1.0, 0.0, 1.0 );
    vertex_colors[1] = color4( 1.0, 1.0, 0.0, 1.0 );
    vertex_colors[2] = color4( 1.0, 1.0, 0.0, 1.0 );
    vertex_colors[3] = color4( 1.0, 1.0, 0.0, 1.0 );

    vertexsTextura = new vec2[NumVertices];
    texture_route = QString("://resources/Fabric_Green_L.jpg");
    capsa = calculCapsa3D();
}

void PlaBase::quad( int a, int b, int c, int d )
{
    colors[Index] = vertex_colors[a]; points[Index] = vertices[a];
    vertexsTextura[Index] = vec2(0.0, 0.0); Index++;
    colors[Index] = vertex_colors[b]; points[Index] = vertices[b];
    vertexsTextura[Index] = vec2(1.0, 0.0); Index++;
    colors[Index] = vertex_colors[c]; points[Index] = vertices[c];
    vertexsTextura[Index] = vec2(1.0, 1.0); Index++;
    colors[Index] = vertex_colors[a]; points[Index] = vertices[a];
    vertexsTextura[Index] = vec2(0.0, 0.0); Index++;
    colors[Index] = vertex_colors[c]; points[Index] = vertices[c];
    vertexsTextura[Index] = vec2(1.0, 1.0); Index++;
    colors[Index] = vertex_colors[d]; points[Index] = vertices[d];
    vertexsTextura[Index] = vec2(0.0, 1.0); Index++;
}

void PlaBase::make()
{
    Index = 0;
    quad( 0, 1, 2, 3 );
    init_textura();
}

PlaBase::~PlaBase()
{

}
