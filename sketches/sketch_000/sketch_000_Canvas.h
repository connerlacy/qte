#ifndef SKETCH_000_CANVAS_H
#define SKETCH_000_CANVAS_H

#include "eio_qte_Include.h"

class sketch_000_Canvas : public Canvas
{
    Q_OBJECT
public:
    explicit sketch_000_Canvas(QWidget *parent = 0) : Canvas(parent) {}

    void setup();
    void draw();

    int m_Time = 0;

    Shader m_Shader;
    Mesh *m_Mesh;

};

#endif // SKETCH_000_CANVAS_H
