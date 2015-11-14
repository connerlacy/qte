#include "sketch_000_Canvas.h"

void sketch_000_Canvas::setup()
{
    //TWOD = 1;

    m_Shader.loadFragmentShader("/Users/connerlacy/Documents/emergent.io/Repositories/eio_qte/sketches/sketch_000/sketch_000_Shader.frag");
    m_Shader.loadVertexShader("/Users/connerlacy/Documents/emergent.io/Repositories/eio_qte/sketches/sketch_000/sketch_000_Shader.vert");
    m_Shader.link();

    m_Mesh = new Mesh;
    m_Mesh->makePlane(40, 40);
    m_Mesh->setColor(QVector4D(1.0,0.4,0.1,1.0));
    m_Mesh->setPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    m_Mesh->createBuffers();
    m_Shader.setAttributeBuffersFromMesh(m_Mesh);

    m_Shader.bind();

    //setClearColor(1.0f,0.0f,0.1f,1.0f);

    //qDebug() << "inds" << m_Mesh->_vertices.size();

    m_Interval = 0.008;
}

void sketch_000_Canvas::draw()
{
    m_Time += m_Interval;

    //qDebug() << m_Time << sin(fmod(m_Time, 0.08));

    QMatrix4x4 mat;
   // mat.translate(0,0,-40);
   // mat.rotate(-70, 1, 0, 0);
    //mat.scale(10.0, 10.0, 1.0);


    m_Shader.setUniformValue("u_time", float(m_Time));
    m_Shader.setUniformValue("u_cameraPosition", QVector3D(m_ArcBall->_xyz));
    m_Shader.setUniformValue("u_mvp_matrix", m_ProjectionMatrix * m_ArcBall->_matrix * mat);

    m_Mesh->setPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    m_Mesh->drawMesh();

   // mat.translate(0,0,2.0);
    m_Shader.setUniformValue("u_mvp_matrix", m_ProjectionMatrix * m_ArcBall->_matrix * mat);
    m_Mesh->setPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    m_Mesh->drawMesh();


}
