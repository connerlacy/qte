#ifndef MESH_H
#define MESH_H

#include <QOpenGLWidget>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QVector3D>
#include <QVector4D>
#include <QQuaternion>
#include <QMatrix4x4>
#include <QOpenGLVertexArrayObject>

#include "eio_qte_ArcBall.h"

#include "gl.h"
#include "glu.h"

class Mesh
{
public:
    Mesh();

    QMatrix4x4 _transformationMatrix;

    GLenum _face, _mode, _primitive;    //OpenGL polygon draw modes

    QVector<QVector3D>  _vertices;  //Vector of vertices
    QVector<QVector4D>  _colors;     //Vecotr of colors
    QVector<GLushort>   _indices;   //Vecotr of indexes into vertex array
    QVector<QVector3D>  _normals;

    //---------------------------------------- SHADERS
    QOpenGLShaderProgram m_shaderProgram;
    void setShaderProgram(QOpenGLShaderProgram& sp);

    QOpenGLBuffer m_PositionBuffer;
    QOpenGLBuffer m_PositionBufferTriple;
    QOpenGLBuffer m_ColorBuffer;
    QOpenGLBuffer m_NormalBuffer;
    QOpenGLBuffer m_TextureUVBuffer;
    QOpenGLBuffer m_IndexBuffer;

    void createBuffers();

    void newVertex(float x, float y, float z);

    void setPolygonMode(GLenum face, GLenum mode);
    void setPrimitive(GLenum primitive);
    void setMultMatrix(QMatrix4x4 mtrx);

    void initIndicies();    //Inits indices to 0 to vertex array size

    //---- Utilities / Helpers
    //Plane
    void makePlane(int rows, int columns);
    void makePlane(int rows, int columns, float unitSize);

    //Circle
    void makeCircle(float radius, float numSlices);
    void makeCircle(float radius, float borderWidth,  float numSlices);

    //Arc
    void makeArc(float radius, float width, float degreeStart, float degreeStop, float numSlices);

    //Sphere
    void makeSphere(float radius, float numLongitude, float numLatitude);

    //Cylinder
    void makeCylinder(float radius, float height, float numLongitude, float numLatitude);
    void makeCylinder(float radius, QVector3D start, QVector3D end, float numLongitude, float numLatitude);

    //Cone
    void makeCone(float radius, float height, float numSlices);

    //---- Draw
    void drawMesh();  //Paints to GL context

    //---- Utilities
    QVector3D getMeshCenter();
    void clear();


};

#endif // MESH_H
