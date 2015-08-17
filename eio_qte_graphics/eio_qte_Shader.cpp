#include "eio_qte_Shader.h"

Shader::Shader(QObject *parent) :
    QOpenGLShaderProgram(parent)
{

}

void Shader::loadVertexShader(QString path)
{
    if (!addShaderFromSourceFile(QOpenGLShader::Vertex, path))
    {
        qCritical() << "Unable to compile vertex shader. Log:" << log();
    }
}

void Shader::loadFragmentShader(QString path)
{
    if (!addShaderFromSourceFile(QOpenGLShader::Fragment, path))
    {
        qCritical() << "Unable to compile fragment shader. Log:" << log();
    }
}

void Shader::linkShaderProgram()
{
    if(!link())
    {
        qCritical() << "Unable to link shader program. Log:" << log();
    }
}

void Shader::setAttributeBuffersFromMesh(Mesh *mesh)
{
    this->bind();

    //Enable Defaults
    mesh->m_PositionBuffer.bind();
    enableAttributeArray("a_position");
    setAttributeBuffer("a_position", GL_FLOAT, 0, 3); //X,Y,Z

    //qDebug() << "buffer id" << mesh->m_PositionBuffer.bufferId();

    mesh->m_ColorBuffer.bind();
    enableAttributeArray("a_color");
    setAttributeBuffer("a_color", GL_FLOAT, 0, 4);

    //mesh->m_IndexBuffer.bind();

    mesh->m_NormalBuffer.bind();
    enableAttributeArray("a_normal");
    setAttributeBuffer("a_normal", GL_FLOAT, 0, 3);

    mesh->m_TextureUVBuffer.bind();
    enableAttributeArray("a_texcoord");
    setAttributeBuffer("a_texcoord", GL_FLOAT, 0, 2);
}

