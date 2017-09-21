#ifndef SKETCH_003_CANVAS_H
#define SKETCH_003_CANVAS_H

#include "eio_qte_Include.h"

class sketch_003_Canvas : public Canvas
{
    Q_OBJECT
public:
    explicit sketch_003_Canvas(QWidget *parent = 0) : Canvas(parent) {}

    void setup();
    void draw();

    int m_Time = 0;

    Shader m_Shader;
    Mesh *m_Mesh;
    ModelLoader model;

    module::Perlin perlin;

};

#endif // SKETCH_003_CANVAS_H
