#include "eio_qte_ArcBall.h"

ArcBall::ArcBall(QObject *parent) :
    QObject(parent)
{
    _translateX = 0;
    _translateY = 0;
    _translateZ = 0;//-5;
}

void ArcBall::setSize(int width, int height)
{
    _width = width;
    _height = height;
}

void ArcBall::click(int x, int y)
{
    _mouseStartX = x;
    _mouseStartY = y;
}

void ArcBall::drag(int x, int y)
{
    // Mouse release position - mouse press position
    QVector2D diff =  QVector2D(x,y) - QVector2D(_mouseStartX,_mouseStartY);

    // Rotation axis is perpendicular to the mouse position difference
    // vector
    QVector3D n = QVector3D(diff.y(), diff.x(), 0.0).normalized();

    // Accelerate angular speed relative to the length of the mouse sweep
    qreal acc = diff.length();// / 100.0;

    _qTo = QQuaternion::fromAxisAndAngle(n, acc) * _qTo;

    _mouseStartX = x;
    _mouseStartY = y;

    updateMatrix();

}

void ArcBall::translate(int x, int y, int z)
{
    _translateX = x;
    _translateY = y;
    _translateZ = z;

    updateMatrix();
}

void ArcBall::updateMatrix()
{
    _matrix.setToIdentity();
    _matrix.translate(_translateX, _translateY, -_translateZ);
    _matrix.rotate(_qTo);
}


