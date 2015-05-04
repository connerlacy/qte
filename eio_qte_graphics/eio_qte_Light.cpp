#include "BeBopSensors_Light.h"

Light::Light(QObject *parent) :
    QObject(parent)
{
    _ambientR = 1.0;
    _ambientG = 1.0;
    _ambientB = 1.0;
    _ambientA = 1.0;

    _diffuseR = 1.0;
    _diffuseG = 1.0;
    _diffuseB = 1.0;
    _diffuseA = 1.0;

    _specularR = 1.0;
    _specularG = 1.0;
    _specularB = 1.0;
    _specularA = 1.0;

    _positionW = 1.0;
    _positionX = 0.0;
    _positionY = 0.0;
    _positionZ = 0.0;
}

void Light::drawLight()
{
    GLfloat light_ambient[] = { _ambientR, _ambientG, _ambientB, _ambientA};
    GLfloat light_diffuse[] = { _diffuseR, _diffuseG, _diffuseB, _diffuseA};
    GLfloat light_specular[] = { _specularR, _specularG, _specularB, _specularA};
    GLfloat light_position[] = { _positionX, _positionY, _positionZ, _positionW };

    glPushMatrix();

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glPopMatrix();
}

/////////////////////////////////////////////////////////////////
///////////////////////////// Position //////////////////////////
/////////////////////////////////////////////////////////////////
void Light::setPosition(QVector3D pos)
{

}

void Light::setPosition(QVector4D pos)
{
    _positionW = pos.w();
    _positionX = pos.x();
    _positionY = pos.y();
    _positionZ = pos.z();
}

void Light::setPosition(GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{

}

void Light::setPosition(GLfloat x, GLfloat y, GLfloat z)
{

}


/////////////////////////////////////////////////////////////////
///////////////////////////// Diffuse ///////////////////////////
/////////////////////////////////////////////////////////////////
void Light::setDiffuse(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{

}

/////////////////////////////////////////////////////////////////
//////////////////////////// Specular ///////////////////////////
/////////////////////////////////////////////////////////////////
void Light::setSpecular(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{

}

/////////////////////////////////////////////////////////////////
///////////////////////////// Ambient ///////////////////////////
/////////////////////////////////////////////////////////////////
void Light::setAmbient(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{

}
