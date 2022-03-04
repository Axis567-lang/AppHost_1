#ifndef PrismaPLUGIN_H
#define PrismaPLUGIN_H

#include "interfaces.h"
#include "vertexdata.h"

#include <QObject>
#include <QtPlugin>

class PrismaPlugin : public QObject,
                   public ShapeInterface
{
    Q_OBJECT

    Q_PLUGIN_METADATA(IID "app-host.OGLWidget.ShapeInterface" FILE "prisma.json")

    Q_INTERFACES(ShapeInterface)

public:

    VertexData *buildVertices(uint &nv);
    uint       *buildIndices (uint &ni);

    QStringList info() { return QStringList() << tr("Prisma"); }

};

#endif
