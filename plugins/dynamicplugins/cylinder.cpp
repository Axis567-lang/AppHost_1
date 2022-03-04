#include "cylinder.h"

///////////////////////////////////////////////////

#include <QtMath>

uint *CylinderPlugin::buildIndices(uint &ni)
{
    ni   = 0;
    return 0;
}

VertexData *CylinderPlugin::buildVertices(uint &nv)
{

    int vertical_degrees = 180;   // vertical degrees
    int horizontal_degrees = 370; // horizontal degrees
    int space = 10;

    int numParalels = vertical_degrees/space + 1;
    int numMeridians = horizontal_degrees/space;

    int    VertexCount = numParalels * numMeridians * 4;

    VertexData *vertices = new VertexData[VertexCount];

    int n = 0;
    int phi = 0;
    double p_radians;

    for ( phi = 0; phi < horizontal_degrees; phi+=space ){

        p_radians = qDegreesToRadians((double)phi);

        vertices[n] = {QVector3D(qSin( p_radians ) ,
                                 -1.0,
                                 qCos( p_radians )
                                )
                       ,
                       QVector2D( (double)phi/horizontal_degrees, 0.0) };
        n++;

        p_radians = qDegreesToRadians( (double)(phi+space) );

        vertices[n] = {QVector3D(qSin( p_radians ) ,
                                 -1.0,
                                 qCos( p_radians )
                                )
                       ,
                       QVector2D( (double)(phi+space)/horizontal_degrees, 0.0)};
        n++;

        p_radians = qDegreesToRadians((double)phi);

        vertices[n] = {QVector3D(qSin( p_radians ) ,
                                 1.0,
                                 qCos( p_radians )
                                )
                       ,
                       QVector2D( (double)phi/horizontal_degrees, 1.0)};
        n++;

        p_radians = qDegreesToRadians( (double)(phi+space) );

        vertices[n] = {QVector3D(qSin( p_radians ) ,
                                 1.0,
                                 qCos( p_radians )
                                )
                       ,
                       QVector2D( (double)(phi+space)/horizontal_degrees, 1.0)};
        n++;



    }

    nv = n;
    return vertices;
}

