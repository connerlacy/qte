#include "sketch_003_Canvas.h"

void sketch_003_Canvas::setup()
{
    //TWOD = 1;

    perlin.SetOctaveCount(2);

    qDebug() << "model" << model.importAsset("/Users/connerlacy/Desktop/sphere.dae");

    m_Shader.loadFragmentShader("/Users/connerlacy/Documents/emergent.io/Repositories/eio_qte/sketches/sketch_003/sketch_003_Shader.frag");
    m_Shader.loadVertexShader("/Users/connerlacy/Documents/emergent.io/Repositories/eio_qte/sketches/sketch_003/sketch_003_Shader.vert");
    m_Shader.link();

    m_Mesh = new Mesh;

    //m_Mesh->makeCylinder(0.5, QVector3D(0,0,0), QVector3D(0,0,0.2), 10, 10);
    //m_Mesh->makeSphere(1.0, 50, 50);
    m_Mesh->setPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    m_Mesh->setPrimitive(GL_QUADS);
    m_Mesh->setColor(QVector4D(1.0,1.0,1.0,1.0));
    m_Mesh->createBuffers();
    m_Shader.setAttributeBuffersFromMesh(m_Mesh);

    m_Shader.bind();

    setClearColor(1.0,1.0,1.0,1.0);
}

void sketch_003_Canvas::draw()
{
    m_Time += m_Interval;

    m_Mesh->setColor(QVector4D(1.0,1.0,1.0,0.25));

    float numLayers = 30;

    m_Shader.bind();
    m_Shader.setUniformValue("u_time", float(m_Time));
    m_Shader.setUniformValue("u_layers", numLayers);
    m_Shader.setUniformValue("u_cameraPosition", QVector3D(m_ArcBall->_xyz));
    m_Shader.setUniformValue("u_mvp_matrix", m_ProjectionMatrix * m_ArcBall->_matrix);

    m_Mesh->drawMesh();
}
