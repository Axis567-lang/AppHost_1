
#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "geometry.h"

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include <QQuaternion>
#include <QVector2D>
#include <QBasicTimer>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QVector>

class Geometry;

class MainWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

    void changeTexture(QString filename);
    void changeShape(Geometry *geo);
    void addShape(Geometry *geo);
    void changeScale(int index, float s_x, float s_y, float s_z);
    void changePosition(int index, float x, float y, float z);

protected:
    void mousePressEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
    void timerEvent(QTimerEvent *e) Q_DECL_OVERRIDE;

    void initializeGL() Q_DECL_OVERRIDE;
    void resizeGL(int w, int h) Q_DECL_OVERRIDE;
    void paintGL() Q_DECL_OVERRIDE;

    void initShaders();
    void initTextures(QString filename);

private:
    QBasicTimer          timer;
    QOpenGLShaderProgram program;

    QVector<Geometry *>    geometries;

    QOpenGLTexture       *texture;

    QMatrix4x4           projection;

    QVector2D            mousePressPosition;
    QVector3D            rotationAxis;
    qreal                angularSpeed;
    QQuaternion          rotation;
};

#endif // MAINWIDGET_H
