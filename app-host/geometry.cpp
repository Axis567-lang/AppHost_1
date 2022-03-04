#include "geometry.h"


Geometry::Geometry()
    : indexBuf(QOpenGLBuffer::IndexBuffer)
{
    initializeOpenGLFunctions();

    // Generate 2 VBOs
    arrayBuf.create();
    indexBuf.create();

    numIndices  = 0;
    numVertices = 0;

    // configure display mode
    displayMode = GL_TRIANGLE_STRIP;

    px = 0.0f; py = 0.0f; pz = 0.0f;
    sx = 1.0f; sy = 1.0f; sz = 1.0f;
}

Geometry::~Geometry()
{
    arrayBuf.destroy();
    indexBuf.destroy();
}

void Geometry::draw(QOpenGLShaderProgram *program)
{
    // Tell OpenGL which VBOs to use
    arrayBuf.bind();
    indexBuf.bind();

    // Offset for position
    quintptr offset = 0;

    // Tell OpenGL programmable pipeline how to locate vertex position data
    int vertexLocation = program->attributeLocation("position");
    program->enableAttributeArray(vertexLocation);
    program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

    // Offset for texture coordinate
    offset += sizeof(QVector3D);

    // Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
    int texcoordLocation = program->attributeLocation("texcoord");
    program->enableAttributeArray(texcoordLocation);
    program->setAttributeBuffer(texcoordLocation, GL_FLOAT, offset, 2, sizeof(VertexData));

    // Draw geometry using indices or vertices arrays
    if ( numIndices > 0 )
        glDrawElements(displayMode, numIndices, GL_UNSIGNED_INT, 0);
    else if ( numVertices > 0 )
        glDrawArrays  (displayMode, 0, numVertices);
}

void Geometry::build(VertexData *vd,    uint numv,
                     uint       *idata, uint numi)
{
    // Transfer vertex data to VBO 0
    arrayBuf.bind();
    numVertices = numv;
    arrayBuf.allocate(vd, numVertices * sizeof(VertexData));

    // Transfer index data to VBO 1
    indexBuf.bind();
    numIndices = numi;
    indexBuf.allocate(idata, numIndices * sizeof(uint));
}


