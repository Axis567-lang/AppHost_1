#include "sphere.h"

///////////////////////////////////////////////////

#include <QtMath>

uint *SpherePlugin::buildIndices(uint &ni)
{
    ni   = 0;
    return 0;
}

VertexData *SpherePlugin::buildVertices(uint &nv)
{

    int vertical_degrees = 180;   // vertical degrees
    int horizontal_degrees = 360; // horizontal degrees
    int space = 10;

    int numParalels = vertical_degrees/space + 1;
    int numMeridians = horizontal_degrees/space;

    int    VertexCount = numParalels * numMeridians * 4;

    VertexData *vertices = new VertexData[VertexCount];

    int n = 0;
    int theta = 0;
    int phi = 0;
    double t_radians,p_radians;

    for ( phi = 0; phi < horizontal_degrees; phi+=space ){
        for( theta = 0; theta <= vertical_degrees; theta+=space){

            t_radians = qDegreesToRadians((double)theta);
            p_radians = qDegreesToRadians((double)phi);

            // pivot points 1
            vertices[n] = {QVector3D(qSin( t_radians )*qSin( p_radians ) ,
                                     qCos( t_radians ) ,
                                     qSin( t_radians )*qCos( p_radians )
                                    )
                           ,
                           QVector2D( (double)phi/horizontal_degrees, (double)theta/vertical_degrees)};
            n++;

            // pivot points 3
            t_radians = qDegreesToRadians((double)(theta+space));
            p_radians = qDegreesToRadians((double)phi);

            vertices[n] = {QVector3D(qSin( t_radians )*qSin( p_radians ) ,
                                     qCos( t_radians ) ,
                                     qSin( t_radians )*qCos( p_radians )
                                    )
                           ,
                           QVector2D( (double)phi/horizontal_degrees, (double)(theta+space)/vertical_degrees)};
            n++;

            // pivot points 2
            t_radians = qDegreesToRadians((double)theta);
            p_radians = qDegreesToRadians( (double)(phi+space) );

            vertices[n] = {QVector3D(qSin( t_radians )*qSin( p_radians ) ,
                                     qCos( t_radians ) ,
                                     qSin( t_radians )*qCos( p_radians )
                                    )
                           ,
                           QVector2D( (double)(phi+space)/horizontal_degrees, (double)theta/vertical_degrees)};
            n++;



            // pivot points 4
            t_radians = qDegreesToRadians((double)(theta+space));
            p_radians = qDegreesToRadians( (double)(phi+space) );

            vertices[n] = {QVector3D(qSin( t_radians )*qSin( p_radians ) ,
                                     qCos( t_radians ) ,
                                     qSin( t_radians )*qCos( p_radians )
                                    )
                           ,
                           QVector2D( (double)(phi+space)/horizontal_degrees, (double)(theta+space)/vertical_degrees)};
            n++;
        }
    }

    nv = n;
    return vertices;
}

