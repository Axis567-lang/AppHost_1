#include "prisma.h"

///////////////////////////////////////////////////

#include <QtMath>

uint *PrismaPlugin::buildIndices(uint &ni)
{
    ni   = 0;
    return 0;
}

VertexData *PrismaPlugin::buildVertices(uint &nv)
{

    int vertical_degrees = 180;   // vertical degrees
    int horizontal_degrees = 1850; // horizontal degrees
    int space = 5;

    int numParalels = vertical_degrees/space + 1;
    int numMeridians = horizontal_degrees/space;

    int    VertexCount = numParalels * numMeridians * 4;

    VertexData *vertices = new VertexData[VertexCount];

    int n = 0;
    int phi = 0;
    double p_radians;

    for ( phi = 0; phi < horizontal_degrees; phi+=space ){

        p_radians = qDegreesToRadians((double)phi);

        vertices[n] = {QVector3D(2*qCos( p_radians )- qCos(2 * p_radians),
                                 -1.0,
                                 2*qSin( p_radians )- qSin(2 * p_radians)
                                )
                       ,
                       QVector2D( (double)phi/horizontal_degrees, 0.0) };
        n++;

        p_radians = qDegreesToRadians( (double)(phi+space) );

        vertices[n] = {QVector3D(2*qCos( p_radians )- qCos(2 * p_radians) ,
                                 -1.0,
                                 2*qSin( p_radians )- qSin(2 * p_radians)
                                )
                       ,
                       QVector2D( (double)(phi+space)/horizontal_degrees, 0.0)};
        n++;

        p_radians = qDegreesToRadians((double)phi);

        vertices[n] = {QVector3D(2*qCos( p_radians )- qCos(2 * p_radians) ,
                                 1.0,
                                 2*qSin( p_radians )- qSin(2 * p_radians)
                                )
                       ,
                       QVector2D( (double)phi/horizontal_degrees, 1.0)};
        n++;

        p_radians = qDegreesToRadians( (double)(phi+space) );

        vertices[n] = {QVector3D(2*qCos( p_radians )- qCos(2 * p_radians) ,
                                 1.0,
                                 2*qSin( p_radians )- qSin(2 * p_radians)
                                )
                       ,
                       QVector2D( (double)(phi+space)/horizontal_degrees, 1.0)};
        n++;



    }

    nv = n;
    return vertices;
}

