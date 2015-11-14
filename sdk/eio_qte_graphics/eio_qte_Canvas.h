#ifndef EIO_QTE_CANVAS_H
#define EIO_QTE_CANVAS_H

#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QMatrix4x4>
#include <QTimer>
#include <QDebug>
#include <QGLFormat>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLFunctions_4_1_Core>

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

    QMatrix4x4 m_ProjectionMatrix;

    QTimer  *m_drawTimer;
    float     m_Interval;

    ArcBall *m_ArcBall;

    QVector4D m_ClearColor;
    void setClearColor(float r, float g, float b, float a);

    bool TWOD = false;

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

#endif // EIO_QTE_CANVAS_H
