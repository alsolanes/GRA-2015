#include "plabase.h"

PlaBase::PlaBase() : Objecte(NumVertices)
{
    vertices[0] = point4( 1, 0, 1, 1.0 );//no es veu res perquè pla paral·lel a y
    vertices[1] = point4( 1, 0,-1, 1.0 );
    vertices[2] = point4(-1, 0,-1, 1.0 );
    vertices[3] = point4(-1, 0, 1, 1.0 );

    vertex_colors[0] = color4( 1.0, 1.0, 0.0, 1.0 );
    vertex_colors[1] = color4( 1.0, 1.0, 0.0, 1.0 );
    vertex_colors[2] = color4( 1.0, 1.0, 0.0, 1.0 );
    vertex_colors[3] = color4( 1.0, 1.0, 0.0, 1.0 );

    make();
}

void PlaBase::quad( int a, int b, int c, int d )
{
    colors[Index] = vertex_colors[a]; points[Index] = vertices[a]; Index++;
    colors[Index] = vertex_colors[b]; points[Index] = vertices[b]; Index++;
    colors[Index] = vertex_colors[c]; points[Index] = vertices[c]; Index++;
    colors[Index] = vertex_colors[a]; points[Index] = vertices[a]; Index++;
    colors[Index] = vertex_colors[c]; points[Index] = vertices[c]; Index++;
    colors[Index] = vertex_colors[d]; points[Index] = vertices[d]; Index++;
}

void PlaBase::make()
{
    Index = 0;
    quad( 0, 1, 2, 3 );
}

PlaBase::~PlaBase()
{

}
