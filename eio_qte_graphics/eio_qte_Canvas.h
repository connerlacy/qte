#ifndef EIO_CANVAS_H
#define EIO_CANVAS_H

#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QMatrix4x4>
#include <QTimer>
#include <QDebug>

#include "gl.h"
#include "glu.h"

#include "eio_qte_ArcBall.h"

class Canvas : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit Canvas(QWidget *parent = 0);

    virtual void setup()=0;
    virtual void draw()=0;

    QTimer  *m_drawTimer;
    int m_Interval;
    ArcBall *m_ArcBall;

    QVector4D m_ClearColor;
    void setClearColor(float r, float g, float b, float a);

    void mouseMoveEvent(QMouseEvent *me);
    void mousePressEvent(QMouseEvent *me);
    void mouseReleaseEvent(QMouseEvent *me);

    bool eventFilter(QObject *obj, QEvent *e);

signals:

protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
};

#endif // EIO_CANVAS_H
