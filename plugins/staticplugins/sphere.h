#ifndef SPHEREPLUGIN_H
#define SPHEREPLUGIN_H

#include "interfaces.h"
#include "vertexdata.h"

#include <QObject>
#include <QtPlugin>

class SpherePlugin : public QObject,
                     public ShapeInterface
{
    Q_OBJECT

    Q_PLUGIN_METADATA(IID "app-host.OGLWidget.ShapeInterface" FILE "sphere.json")

    Q_INTERFACES(ShapeInterface)

public:

    VertexData *buildVertices(uint &nv);
    uint       *buildIndices (uint &ni);

    QStringList info() { return QStringList() << tr("Esfera"); }

};

#endif // SPHEREPLUGIN_H
