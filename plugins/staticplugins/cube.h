
#ifndef Cube_H
#define Cube_H


#include "interfaces.h"
#include "vertexdata.h"

#include <QObject>
#include <QtPlugin>

class CubePlugin : public QObject,
                   public ShapeInterface
{
    Q_OBJECT

    Q_PLUGIN_METADATA(IID "app-host.OGLWidget.ShapeInterface" FILE "cube.json")

    Q_INTERFACES(ShapeInterface)

public:

    VertexData *buildVertices(uint &nv);
    uint       *buildIndices (uint &ni);

    QStringList info() { return QStringList() << tr("Cubo"); }

};

#endif // Cube_H
