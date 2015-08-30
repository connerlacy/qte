#ifndef EIO_QTE_SHADER_H
#define EIO_QTE_SHADER_H

#include <QOpenGLShaderProgram>

#include "eio_qte_Include.h"

class Shader : public QOpenGLShaderProgram
{
    Q_OBJECT
public:
    explicit Shader(QObject *parent = 0);

    QOpenGLBuffer m_PositionBuffer;
    QOpenGLBuffer m_ColorBuffer;
    QOpenGLBuffer m_NormalBuffer;
    QOpenGLBuffer m_TextureUVBuffer;
    QOpenGLBuffer m_IndexBuffer;

    void loadVertexShader(QString path);
    void loadFragmentShader(QString path);
    void linkShaderProgram();

    void setAttributeBuffersFromMesh(Mesh *mesh);

signals:

public slots:

};

#endif // EIO_QTE_SHADER_H
