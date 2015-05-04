#ifndef ARCBALL_H
#define ARCBALL_H

#include <QWidget>
#include <QDebug>
#include <QMouseEvent>
#include <QVector3D>
#include <QVector4D>
#include <QQuaternion>
#include <QMatrix4x4>

#include "math.h"

class ArcBall : public QObject
{
    Q_OBJECT
public:
    explicit ArcBall(QObject *parent = 0);

    QQuaternion _qTo;
    int _width, _height;
    float _mouseStartX, _mouseStartY, _mouseEndX, _mouseEndY;
    QMatrix4x4 _matrix;
    float _translateX, _translateY, _translateZ;

    void        setSize(int width, int height);
    void        click(int x, int y);
    void        drag(int x, int y);
    void        translate(int x, int y, int z);

    void        updateMatrix();


signals:
    void signal_RotationAxisAngle(QVector4D vec);

public slots:

};

#endif // ARCBALL_H
