#ifndef SKETCH_001_CANVAS_H
#define SKETCH_001_CANVAS_H

#include "eio_qte_Include.h"
#include "noise.h"

using namespace noise;

class sketch_001_Canvas : public Canvas
{
    Q_OBJECT
public:
    explicit sketch_001_Canvas(QWidget *parent = 0) : Canvas(parent) {}

    void setup();
    void draw();

    int m_Time = 0;

    Shader m_Shader;
    Mesh *m_Mesh;

    module::Perlin myModule;

};

#endif // SKETCH_001_CANVAS_H
