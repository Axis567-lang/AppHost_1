#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include "vertexdata.h"

class Geometry : protected QOpenGLFunctions
{
public:
    Geometry();
    ~Geometry();

    void draw(QOpenGLShaderProgram *program);

    void build(VertexData *vd,    uint numv,
               uint       *idata, uint numi);

    // Specifies what kind of primitives to render.
    // Symbolic constants GL_POINTS, GL_LINE_STRIP,
    // GL_LINE_LOOP, GL_LINES, GL_LINE_STRIP_ADJACENCY,
    // GL_LINES_ADJACENCY, GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN,
    // GL_TRIANGLES, GL_TRIANGLE_STRIP_ADJACENCY, GL_TRIANGLES_ADJACENCY
    // and GL_PATCHES are accepted.
    void setDisplayMode(GLenum mode ){ displayMode = mode; }

    float    px, py, pz;
    float    sx, sy, sz;

protected:

    QOpenGLBuffer arrayBuf; // Data    buffer
    QOpenGLBuffer indexBuf; // Indices buffer

    int numVertices;  // Number of vertices
    int numIndices;   // Number of indices

    int displayMode;  // OpenGL Display mode


};

#endif // GEOMETRY_H
