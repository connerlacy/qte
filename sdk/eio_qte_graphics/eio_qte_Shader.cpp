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

    //---- Position
    mesh->m_PositionBuffer.bind();
    enableAttributeArray("a_position");
    setAttributeBuffer("a_position", GL_FLOAT, 0, 3);   // X,Y,Z

    //---- Color
    mesh->m_ColorBuffer.bind();
    enableAttributeArray("a_color");
    setAttributeBuffer("a_color", GL_FLOAT, 0, 4);      //R, G, B, A

    //---- Normal
    mesh->m_NormalBuffer.bind();
    enableAttributeArray("a_normal");
    setAttributeBuffer("a_normal", GL_FLOAT, 0, 3);     // X, Y, Z

    //---- Texture
    mesh->m_TextureUVBuffer.bind();
    enableAttributeArray("a_texcoord");
    setAttributeBuffer("a_texcoord", GL_FLOAT, 0, 2);   // X, Y
}

