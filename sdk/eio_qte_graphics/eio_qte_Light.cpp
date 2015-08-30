#include "eio_qte_Light.h"

Light::Light(QObject *parent) :
    QObject(parent)
{
    m_AmbientR = 1.0;
    m_AmbientG = 1.0;
    m_AmbientB = 1.0;
    m_AmbientA = 1.0;

    m_DiffuseR = 1.0;
    m_DiffuseG = 1.0;
    m_DiffuseB = 1.0;
    m_DiffuseA = 1.0;

    m_SpecularR = 1.0;
    m_SpecularG = 1.0;
    m_SpecularB = 1.0;
    m_SpecularA = 1.0;

    m_PositionW = 1.0;
    m_PositionX = 0.0;
    m_PositionY = 0.0;
    m_PositionZ = 0.0;
}

void Light::draw()
{
     /*
    GLfloat global_ambient[] = { 1, 1, 1, 1 };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);

    GLfloat light_Ambient[] = { m_AmbientR, m_AmbientG, m_AmbientB, m_AmbientA };
    GLfloat light_Diffuse[] = { m_DiffuseR, m_DiffuseG, m_DiffuseB, m_DiffuseA };
    GLfloat light_Specular[] = { m_SpecularR, m_SpecularG, m_SpecularB, m_SpecularA };
    GLfloat light_Position[] = { m_PositionX, m_PositionY, m_PositionZ, m_PositionW };

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_Ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_Diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_Specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_Position);
    */

    glPushMatrix();

    glEnable(GL_LIGHT0);


    GLfloat global_ambient[] = { 1, 1, 1, 1 };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);

    GLfloat specular[] = {0.2f, 0.2f, 0.2f, 1};
    //glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

    GLfloat ambient[] = { 0.5f, 0.5f, 0.5f, 1 };
    //glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);

    GLfloat diffuse[] = { 0.5f, 0.5f, 0.5f };
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);

    //GLfloat position[] = { 0, 50, 50, 1.0f };
    GLfloat position[] = { m_PositionX, m_PositionY, m_PositionZ, 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, position);

    //qDebug() << m_PositionX << m_PositionY << m_PositionZ;

    //qDebug() << m_PositionX << m_PositionY << m_PositionZ;

    //glLightf (GL_LIGHT0, GL_SPOT_CUTOFF, 45.0f);
    // Fairly shiny spot
    //glLightf(GL_LIGHT0,GL_SPOT_EXPONENT,100.0f);

    //glLightf(GL_LIGHT0, GL_SHININESS, 128);

    glPopMatrix();


}

/////////////////////////////////////////////////////////////////
///////////////////////////// Position //////////////////////////
/////////////////////////////////////////////////////////////////
void Light::setPosition(QVector3D pos)
{
    m_PositionX = pos.x();
    m_PositionY = pos.y();
    m_PositionZ = pos.z();
}

void Light::setPosition(QVector4D pos)
{
    m_PositionW = pos.w();
    m_PositionX = pos.x();
    m_PositionY = pos.y();
    m_PositionZ = pos.z();
}

void Light::setPosition(GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
    m_PositionW = w;
    m_PositionX = x;
    m_PositionY = y;
    m_PositionZ = z;
}

void Light::setPosition(GLfloat x, GLfloat y, GLfloat z)
{
    m_PositionX = x;
    m_PositionY = y;
    m_PositionZ = z;
}


/////////////////////////////////////////////////////////////////
///////////////////////////// Diffuse ///////////////////////////
/////////////////////////////////////////////////////////////////
void Light::setDiffuse(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
    m_DiffuseR = r;
    m_DiffuseG = g;
    m_DiffuseB = b;
    m_DiffuseA = a;
}

/////////////////////////////////////////////////////////////////
//////////////////////////// Specular ///////////////////////////
/////////////////////////////////////////////////////////////////
void Light::setSpecular(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
    m_SpecularR = r;
    m_SpecularG = g;
    m_SpecularB = b;
    m_SpecularA = a;
}

/////////////////////////////////////////////////////////////////
///////////////////////////// Ambient ///////////////////////////
/////////////////////////////////////////////////////////////////
void Light::setAmbient(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
    m_AmbientR = r;
    m_AmbientG = g;
    m_AmbientB = b;
    m_AmbientA = a;
}
