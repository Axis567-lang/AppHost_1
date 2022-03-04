#include "cube.h"

///////////////////////////////////////////////////


VertexData *CubePlugin::buildVertices(uint &nv)
{
    // For cube we would need only 8 vertices but we have to
    // duplicate vertex for each face because texture coordinate
    // is different.
    VertexData *vertices = new VertexData[24];
    // Vertex data for face 0
    vertices[0] = {QVector3D(-1.0f, -1.0f,  1.0f), QVector2D(0.0f, 0.0f)};
    vertices[1] = {QVector3D( 1.0f, -1.0f,  1.0f), QVector2D(0.33f, 0.0f)};
    vertices[2] = {QVector3D(-1.0f,  1.0f,  1.0f), QVector2D(0.0f, 0.5f)};
    vertices[3] = {QVector3D( 1.0f,  1.0f,  1.0f), QVector2D(0.33f, 0.5f)};
    // Vertex data for face 1
    vertices[4] = {QVector3D( 1.0f, -1.0f,  1.0f), QVector2D( 0.0f, 0.5f)};
    vertices[5] = {QVector3D( 1.0f, -1.0f, -1.0f), QVector2D(0.33f, 0.5f)};
    vertices[6] = {QVector3D( 1.0f,  1.0f,  1.0f), QVector2D(0.0f, 1.0f)};
    vertices[7] = {QVector3D( 1.0f,  1.0f, -1.0f), QVector2D(0.33f, 1.0f)};
    // Vertex data for face 2
    vertices[8] = {QVector3D( 1.0f, -1.0f, -1.0f), QVector2D(0.66f, 0.5f)};
    vertices[9] = {QVector3D(-1.0f, -1.0f, -1.0f), QVector2D(1.0f, 0.5f)};
    vertices[10] = {QVector3D( 1.0f,  1.0f, -1.0f), QVector2D(0.66f, 1.0f)};
    vertices[11] = {QVector3D(-1.0f,  1.0f, -1.0f), QVector2D(1.0f, 1.0f)};
    // Vertex data for face 3
    vertices[12] = {QVector3D(-1.0f, -1.0f, -1.0f), QVector2D(0.66f, 0.0f)};
    vertices[13] = {QVector3D(-1.0f, -1.0f,  1.0f), QVector2D(1.0f, 0.0f)};
    vertices[14] = {QVector3D(-1.0f,  1.0f, -1.0f), QVector2D(0.66f, 0.5f)};
    vertices[15] = {QVector3D(-1.0f,  1.0f,  1.0f), QVector2D(1.0f, 0.5f)};
    // Vertex data for face 4
    vertices[16] = {QVector3D(-1.0f, -1.0f, -1.0f), QVector2D(0.33f, 0.0f)};
    vertices[17] = {QVector3D( 1.0f, -1.0f, -1.0f), QVector2D(0.66f, 0.0f)};
    vertices[18] = {QVector3D(-1.0f, -1.0f,  1.0f), QVector2D(0.33f, 0.5f)};
    vertices[19] = {QVector3D( 1.0f, -1.0f,  1.0f), QVector2D(0.66f, 0.5f)};
    // Vertex data for face 5
    vertices[20] = {QVector3D(-1.0f,  1.0f,  1.0f), QVector2D(0.33f, 0.5f)};
    vertices[21] = {QVector3D( 1.0f,  1.0f,  1.0f), QVector2D(0.66f, 0.5f)};
    vertices[22] = {QVector3D(-1.0f,  1.0f, -1.0f), QVector2D(0.33f, 1.0f)};
    vertices[23] = {QVector3D( 1.0f,  1.0f, -1.0f), QVector2D(0.66f, 1.0f)};

    nv = 24;
    return vertices;

}

uint *CubePlugin::buildIndices(uint &ni)
{
    // Indices for drawing cube faces using triangle strips.
    // Triangle strips can be connected by duplicating indices
    // between the strips. If connecting strips have opposite
    // vertex order then last index of the first strip and first
    // index of the second strip needs to be duplicated. If
    // connecting strips have same vertex order then only last
    // index of the first strip needs to be duplicated.
    uint *indices = new uint[34];
    // Face 0 - triangle strip ( v0,  v1,  v2,  v3)
    indices[ 0] = 0; indices[ 1] = 1; indices[ 2] = 2; indices[ 3] = 3; indices[ 4] = 3;
    // Face 1 - triangle strip ( v4,  v5,  v6,  v7)
    indices[ 5] = 4; indices[ 6] = 4; indices[ 7] = 5; indices[ 8] = 6; indices[ 9] = 7; indices[10] = 7;
    // Face 2 - triangle strip ( v8,  v9, v10, v11)
    indices[11] = 8; indices[12] = 8; indices[13] = 9; indices[14] = 10; indices[15] = 11; indices[16] = 11;
    // Face 3 - triangle strip (v12, v13, v14, v15)
    indices[17] = 12; indices[18] = 12; indices[19] = 13; indices[20] = 14; indices[21] = 15; indices[22] = 15;
    // Face 4 - triangle strip (v16, v17, v18, v19)
    indices[23] = 16; indices[24] = 16; indices[25] = 17; indices[26] = 18; indices[27] = 19; indices[28] = 19;
    // Face 5 - triangle strip (v20, v21, v22, v23)
    indices[29] = 20; indices[30] = 20; indices[31] = 21; indices[32] = 22; indices[33] = 23;

    ni = 34;
    return indices;
}

