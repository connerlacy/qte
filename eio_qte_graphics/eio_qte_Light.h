#ifndef LIGHT_H
#define LIGHT_H

#include <QOpenGLWidget>
#include <QVector3D>
#include <QVector4D>
#include <QQuaternion>

#include "gl.h"
#include "glu.h"

class Light : public QObject
{
    Q_OBJECT
public:
    explicit Light(QObject *parent = 0);

    //---- Position
    GLfloat _positionX, _positionY, _positionZ, _positionW; //W specifies directional or positional
    void setPosition(QVector3D pos);
    void setPosition(QVector4D pos);
    void setPosition(GLfloat x, GLfloat y, GLfloat z, GLfloat w);
    void setPosition(GLfloat x, GLfloat y, GLfloat z);

    //---- Diffuse
    GLfloat _diffuseR, _diffuseG, _diffuseB, _diffuseA;
    void setDiffuse(GLfloat r, GLfloat g, GLfloat b, GLfloat a);

    //---- Specular
    GLfloat _specularR, _specularG, _specularB, _specularA;
    void setSpecular(GLfloat r, GLfloat g, GLfloat b, GLfloat a);

    //---- Ambient
    GLfloat _ambientR, _ambientG, _ambientB, _ambientA;
    void setAmbient(GLfloat r, GLfloat g, GLfloat b, GLfloat a);

    void drawLight();

signals:

public slots:

};

#endif // LIGHT_H
