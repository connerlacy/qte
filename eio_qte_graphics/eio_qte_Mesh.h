#ifndef MESH_H
#define MESH_H

#include <QOpenGLWidget>
#include <QVector3D>
#include <QVector4D>
#include <QQuaternion>
#include <QMatrix4x4>

#include "eio_qte_ArcBall.h"

#include "gl.h"
#include "glu.h"

class Mesh
{
public:
    Mesh();
    Mesh(int size);
    Mesh(QVector<QVector3D> verticies);

    int _size; //Num verticies

    QVector3D _translation; //Position in 3D space
    QVector4D _rotation; //Angle, x, y, z
    QMatrix4x4 _transformationMatrix;

    GLenum _face, _mode, _primitive;    //OpenGL polygon draw modes

    QVector<QVector3D>  _verticies;  //Vector of verticies
    QVector<QVector4D>  _colors;     //Vecotr of colors
    QVector<GLushort>   _indicies;   //Vecotr of indexes into vertex array
    QVector<QVector3D>    _normals;

    void newVertex(float x, float y, float z);
    void newIndex(int vertNum);

    //---- Getters
    QVector<QVector3D>  getVerticies(); //Returns list of verts above
    QVector<QVector4D>  getColors();    //Returns list of colors above
    QVector<GLushort>   getIndicies();  //Returns list of indicies above
    int getVertexAtIndex(int index);

    QMatrix4x4 getMultMatrix();

    //---- Setters
    void setVertexX(int vertNum, float x);
    void setVertexY(int vertNum, float y);
    void setVertexZ(int vertNum, float z);
    void setVertex(int vertNum, QVector3D vec);
    void setVertexRGBA(int vertNum, float r, float g, float b, float a);
    void setVertexColor(int vertNum, QColor color);
    void setAllVerticiesToColor(QColor color);

    void setPolygonMode(GLenum face, GLenum mode);
    void setPrimitive(GLenum primitive);

    void setHidden(bool hide);
    bool _isHidden;

    void setTranslation(QVector3D translation); //Position in 3D space
    void setRotation(float angle, float x, float y, float z); //Pitch, roll, yaw
    void setIndicies(QVector<int> indicies);
    void setNormals(QVector<QVector3D> normals) { _normals = normals;}
    void setColors(QVector<QVector4D> colors) {_colors = colors;}

    void setMultMatrix(QMatrix4x4 mtrx);
    //void setTransformMatrix(QMatrix4x4 mtrx);


    //---- Building, Drawing

    void initColors();      //Creates color map corresponding to verticies
    void initIndicies();    //Inits indicies to 0 to vertex array size

    //---- Utilities / Helpers
    //Plane
    void makePlane(int rows, int columns);
    void makePlane(int rows, int columns, float unitSize);

    //Circle
    void makeCircle(float radius, float numSlices);

    //Arc
    void makeArc(float radius, float degreeStart, float degreeStop, float numSlices);

    //Sphere
    void makeSphere(float radius, float numLongitude, float numLatitude);

    //Cylinder
    void makeCylinder(float radius, float height, float numLongitude, float numLatitude);
    void makeCylinder(float radius, QVector3D start, QVector3D end, float numLongitude, float numLatitude);

    //Cone
    void makeCone(float radius, float height, float numSlices);

    //---- Material
    GLfloat _materialAmbient[4];
    GLfloat _materialDiffuse[4];
    GLfloat _materialSpecular[4];
    GLfloat _materialShininess[1];
    GLfloat _materialEmission[4];

    void setMaterialAmbient(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
    void setMaterialDiffuse(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
    void setMaterialSpecular(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
    void setMaterialEmission(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
    void setMaterialShininess(GLfloat level);

    //---- Lighting
    bool _lightingEnabled;
    void setLightingEnabled(bool enabledDisabled);


    //---- ArcBall
    ArcBall *_arcBall;
    bool _arcBallEnable;
    void setArcBall(ArcBall *ab);
    void setArcBallEnable(bool enableDisable);

    //---- Draw
    void drawMesh();  //Paints to GL context
    void drawFaces();
    void drawWireframe();

    //---- Color
    void setColor(float r, float g, float b);

    //---- Utilities
    QVector3D getMeshCenter();
    void clear();


};

#endif // MESH_H
