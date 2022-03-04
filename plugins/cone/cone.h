#ifndef ConePLUGIN_H
#define ConePLUGIN_H

#include "interfaces.h"
#include "vertexdata.h"

#include <QObject>
#include <QtPlugin>

class ConePlugin : public QObject,
                   public ShapeInterface
{
    Q_OBJECT

    Q_PLUGIN_METADATA(IID "app-host.OGLWidget.ShapeInterface" FILE "cone.json")

    Q_INTERFACES(ShapeInterface)

public:

    VertexData *buildVertices(uint &nv);
    uint       *buildIndices (uint &ni);

    QStringList info() { return QStringList() << tr("Cone"); }

};

#endif // ConePLUGIN_H
