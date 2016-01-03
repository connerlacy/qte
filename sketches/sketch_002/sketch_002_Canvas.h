#ifndef SKETCH_002_CANVAS_H
#define SKETCH_002_CANVAS_H

#include "eio_qte_Include.h"

#include <QOpenGLFramebufferObject>
#include <QOpenGLTexture>

class sketch_002_Canvas : public Canvas
{
    Q_OBJECT
public:
    explicit sketch_002_Canvas(QWidget *parent = 0) : Canvas(parent) {}

    void setup();
    void draw();

    float m_Time = 0;

    Shader m_Shader;
    Mesh *m_Mesh;
    QOpenGLFramebufferObject *fbo;
    QOpenGLTexture *texture;

};

#endif // SKETCH_002_CANVAS_H
