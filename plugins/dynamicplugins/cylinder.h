#ifndef CYLINDERPLUGIN_H
#define CYLINDERPLUGIN_H

#include "interfaces.h"
#include "vertexdata.h"

#include <QObject>
#include <QtPlugin>

class CylinderPlugin : public QObject,
                   public ShapeInterface
{
    Q_OBJECT

    Q_PLUGIN_METADATA(IID "app-host.OGLWidget.ShapeInterface" FILE "cylinder.json")

    Q_INTERFACES(ShapeInterface)

public:

    VertexData *buildVertices(uint &nv);
    uint       *buildIndices (uint &ni);

    QStringList info() { return QStringList() << tr("Cilindro"); }

};

#endif // CYLINDERPLUGIN_H
