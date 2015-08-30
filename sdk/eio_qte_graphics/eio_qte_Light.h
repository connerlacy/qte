#ifndef LIGHT_H
#define LIGHT_H

#include <QOpenGLWidget>
#include <QVector3D>
#include <QVector4D>
#include <QQuaternion>
#include <QDebug>

#include "gl.h"
#include "glu.h"

class Light : public QObject
{
    Q_OBJECT
public:
    explicit Light(QObject *parent = 0);

    //---- Position
    GLfloat m_PositionX, m_PositionY, m_PositionZ, m_PositionW; //W specifies directional or positional
    void setPosition(QVector3D pos);
    void setPosition(QVector4D pos);
    void setPosition(GLfloat x, GLfloat y, GLfloat z, GLfloat w);
    void setPosition(GLfloat x, GLfloat y, GLfloat z);

    //---- Diffuse
    GLfloat m_DiffuseR, m_DiffuseG, m_DiffuseB, m_DiffuseA;
    void setDiffuse(GLfloat r, GLfloat g, GLfloat b, GLfloat a);

    //---- Specular
    GLfloat m_SpecularR, m_SpecularG, m_SpecularB, m_SpecularA;
    void setSpecular(GLfloat r, GLfloat g, GLfloat b, GLfloat a);

    //---- Ambient
    GLfloat m_AmbientR, m_AmbientG, m_AmbientB, m_AmbientA;
    void setAmbient(GLfloat r, GLfloat g, GLfloat b, GLfloat a);

    //---- Shininess
    GLfloat m_Shininess;

    void draw();

};

#endif // LIGHT_H
