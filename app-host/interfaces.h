#ifndef INTERFACES_H
#define INTERFACES_H

#include <QtPlugin>
QT_BEGIN_NAMESPACE
#include "vertexdata.h"
#include <QStringList>
QT_END_NAMESPACE

class ShapeInterface
{

public:
    virtual ~ShapeInterface(){}

    virtual VertexData *buildVertices(uint &nv)=0;
    virtual uint       *buildIndices (uint &ni)=0;

    virtual QStringList info() = 0;

};

QT_BEGIN_NAMESPACE

#define ShapeInterface_iid "app-host.OGLWidget.ShapeInterface"

Q_DECLARE_INTERFACE(ShapeInterface, ShapeInterface_iid)

QT_END_NAMESPACE

#endif // INTERFACES_H
