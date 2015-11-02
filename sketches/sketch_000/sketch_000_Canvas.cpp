#include "sketch_000_Canvas.h"

void sketch_000_Canvas::setup()
{
    //TWOD = 1;

    m_Shader.loadFragmentShader("/Users/connerlacy/Documents/emergent.io/Repositories/eio_qte/sketches/sketch_000/sketch_000_Shader.frag");
    m_Shader.loadVertexShader("/Users/connerlacy/Documents/emergent.io/Repositories/eio_qte/sketches/sketch_000/sketch_000_Shader.vert");
    m_Shader.link();

    m_Mesh = new Mesh;
    m_Mesh->makePlane(10, 10, 1);
    m_Mesh->setColor(QVector4D(1,0.5,0.5,1.0));
    m_Mesh->createBuffers();
    m_Shader.setAttributeBuffersFromMesh(m_Mesh);

    m_Shader.bind();
}

void sketch_000_Canvas::draw()
{
    m_Time += m_Interval;

    m_Shader.setUniformValue("u_time", float(m_Time));
    m_Shader.setUniformValue("u_cameraPosition", QVector3D(m_ArcBall->_xyz));
    m_Shader.setUniformValue("u_mvp_matrix", m_ProjectionMatrix * m_ArcBall->_matrix);

    m_Mesh->drawMesh();
}
