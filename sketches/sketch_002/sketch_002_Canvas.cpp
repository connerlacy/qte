#include "sketch_002_Canvas.h"

void sketch_002_Canvas::setup()
{
    TWOD = 0;

    //fbo = new QOpenGLFramebufferObject;

    m_Shader.loadFragmentShader("/Users/connerlacy/Documents/emergent.io/Repositories/eio_qte/sketches/sketch_002/sketch_002_Shader.frag");
    m_Shader.loadVertexShader("/Users/connerlacy/Documents/emergent.io/Repositories/eio_qte/sketches/sketch_002/sketch_002_Shader.vert");
    m_Shader.link();

    m_Mesh = new Mesh;
    //m_Mesh->makePlane(16, 16, 1);
    m_Mesh->makeLine(100.0, 200);
    m_Mesh->setColor(QVector4D(1,0.5,0.5,1.0));
    m_Mesh->createBuffers();

    m_Shader.setAttributeBuffersFromMesh(m_Mesh);
    m_Shader.bind();

    m_Mesh->setPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    m_Mesh->setPrimitive(GL_LINE_STRIP);

    m_Interval = 20;

    // Load cube.png image
    texture = new QOpenGLTexture(QImage("/Users/connerlacy/Pictures/IMG_1336.JPG").mirrored());

    //texture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
    //texture->setMagnificationFilter(QOpenGLTexture::Linear);

    // Set nearest filtering mode for texture minification
  texture->setMinificationFilter(QOpenGLTexture::Nearest);

    // Set bilinear filtering mode for texture magnification
    texture->setMagnificationFilter(QOpenGLTexture::Linear);

    // Wrap texture coordinates by repeating
    // f.ex. texture coordinate (1.1, 1.2) is same as (0.1, 0.2)
    //texture->setWrapMode(QOpenGLTexture::Repeat);


}

void sketch_002_Canvas::draw()
{
    m_Time += 0.001;

    QMatrix4x4 mat;

    //mat.rotate(90, 0, 1, 0);
    //mat.translate(-5,0,0);

    texture->bind();
    m_Shader.setUniformValue("u_time", float(m_Time));
    //m_Shader.setUniformValue("u_cameraPosition", QVector3D(m_ArcBall->_xyz));
    m_Shader.setUniformValue("u_mvp_matrix", m_ProjectionMatrix * m_ArcBall->_matrix * mat);
    m_Shader.setUniformValue("src_tex_unit0", 0);

    //qDebug() << "m_Time" << m_Time;

    m_Mesh->drawMesh();
}
