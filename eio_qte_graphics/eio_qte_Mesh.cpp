#include "BeBopSensors_Mesh.h"

Mesh::Mesh() :
    _face(GL_FRONT_AND_BACK),
    _mode(GL_LINE),
    _primitive(GL_POINTS)
{
    _arcBall = NULL;

    setMaterialAmbient(0.1, 0.1, 0.1, 1.0);
    setMaterialDiffuse(1.0, 0.0, 0.0, 1.0);
    setMaterialSpecular(0.5, 0.5, 0.5, 1.0);
    setMaterialEmission(0.1, 0.1, 0.1, 1.0);
    setMaterialShininess(50.0);

    //setMaterialAmbient(0.19225, 0.19225, 0.19225,1);
    //setMaterialDiffuse(0.50754,0.50754,0.50754,1);
    //setMaterialSpecular(0.508273,	0.508273,	0.508273,1);
    //setMaterialEmission(0.1, 0.1, 0.1, 1.0);
    //setMaterialShininess(50);

    _lightingEnabled = false;

    _isHidden = false;
}

Mesh::Mesh(int size) :
    _face(GL_FRONT_AND_BACK),
    _mode(GL_LINE),
    _primitive(GL_POINTS)
{
    _size = size;
}

Mesh::Mesh(QVector<QVector3D> verticies) :
    _face(GL_FRONT_AND_BACK),
    _mode(GL_LINE),
    _primitive(GL_POINTS)
{
    setMaterialAmbient(0.1, 0.1, 0.1, 1.0);
    setMaterialDiffuse(1.0, 0.0, 0.0, 1.0);
    setMaterialSpecular(0.5, 0.5, 0.5, 1.0);
    //setMaterialEmission(0.1, 0.1, 0.1, 1.0);
    //setMaterialShininess(50.0);

    setMaterialAmbient(0.19225, 0.19225, 0.19225,1);
    setMaterialDiffuse(0.50754,0.50754,0.50754,1);
    setMaterialSpecular(0.508273,	0.508273,	0.508273,1);
    //setMaterialEmission(0.1, 0.1, 0.1, 1.0);
    setMaterialShininess(100);

    _isHidden = false;

    _verticies.clear();

    _verticies = verticies;

    for(int i = 0; i < verticies.size(); i++)
    {
        //qDebug() << "mesh verticies" << verticies.at(i);
    }

    initIndicies();
    initColors();

    //qDebug() << "mesh indicies size" << _indicies.size() << _indicies;
    //qDebug() << "mesh _verts size" << _verticies.size() << _verticies;
}

void Mesh::newVertex(float x, float y, float z)
{
    _verticies.append(QVector3D(x,y,z));

    //Recalculate indicies linearly
    initIndicies();

    //Colors will also need to be updated
    initColors();

}

void Mesh::newIndex(int vertNum)
{

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////// GETTERS //////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
QVector<QVector3D> Mesh::getVerticies()
{
    return _verticies;
}

int Mesh::getVertexAtIndex(int index)
{
    if(index < _indicies.size())
    {
        return _indicies.at(index);
    }

    return -1;
}

QVector<QVector4D> Mesh::getColors()
{
    return _colors;
}

QVector<GLushort> Mesh::getIndicies()
{
    return _indicies;
}

QMatrix4x4 Mesh::getMultMatrix()
{
    return _transformationMatrix;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////// SETTERS //////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

//----------------------------------------- Vertex Position --------------------------------------------//
void Mesh::setVertex(int vertNum, QVector3D vec)
{
    _verticies.replace(vertNum, vec);
}

void Mesh::setVertexX(int vertNum, float x)
{
    QVector3D vec = _verticies.at(vertNum);
    vec.setX(x);
    _verticies.replace(vertNum, vec);
}

void Mesh::setVertexY(int vertNum, float y)
{
    QVector3D vec = _verticies.at(vertNum);
    vec.setY(y);
    _verticies.replace(vertNum, vec);
}

void Mesh::setVertexZ(int vertNum, float z)
{
    QVector3D vec = _verticies.at(vertNum);
    vec.setZ(z);
    _verticies.replace(vertNum, vec);
}

//----------------------------------------- Vertex Color --------------------------------------------//
void Mesh::setVertexRGBA(int vertNum, float r, float g, float b, float a)
{
    QVector4D vec = QVector4D(r, g, b, a);
    _colors.replace(vertNum, vec);
    //_colors.at(vertNum).setX(r);
}

void Mesh::setVertexColor(int vertNum, QColor color)
{
    QVector4D vec = QVector4D(color.redF(), color.greenF(), color.blueF(), color.alphaF());
    _colors.replace(vertNum, vec);
}

void Mesh::initColors()
{
    //----------------- Construct color data
    _colors.clear();

    for(int i = 0; i < _verticies.size(); i++)
    {
        float r = (float)qrand()/(float)RAND_MAX;
        float g = (float)qrand()/(float)RAND_MAX;
        float b = (float)qrand()/(float)RAND_MAX;
        //_colors.append(QVector4D(r,g,b,1));
        _colors.append(QVector4D(0.0,0.0,0.0,1.0));
    }
}

void Mesh::setAllVerticiesToColor(QColor color)
{
    _colors.clear();

    for(int i = 0; i < _verticies.size(); i++)
    {
        _colors.append(QVector4D((float)color.red()/255.0f, (float)color.green()/255.0f, (float)color.blue()/255.0f, (float)color.alpha()/255.0f));
        //_colors.append(QVector4D(1.0,0.0,0.0,1.0));
    }
}


//-------------------------------------------- Indexing ----------------------------------------------//
void Mesh::setIndicies(QVector<int> indicies)
{
    _indicies.clear();

    for(int i = 0; i < indicies.size(); i++)
    {
        _indicies.append(indicies.at(i));
    }
}

void Mesh::initIndicies()
{
    _indicies.clear();

    for(int i = 0; i < _verticies.size(); i++)
    {
        _indicies.append(i);
    }
}


//---------------------------------------- Transformations -------------------------------------------//
void Mesh::setTranslation(QVector3D translation)
{
    //qDebug() << "Set translation in mesh" << translation;
    _translation = translation;
}

void Mesh::setRotation(float angle, float x, float y, float z)
{
    _rotation = QVector4D(x, y, z, angle);

    //_rotation.setX(x);
    //_rotation.setY(y);
    //_rotation.setZ(z);
}

void Mesh::setMultMatrix(QMatrix4x4 mtrx)
{
    _transformationMatrix = mtrx;
}


//----------------------------------------- OpenGL Settings -------------------------------------------//
void Mesh::setPolygonMode(GLenum face, GLenum mode)
{
    _face = face;
    _mode = mode;
}

void Mesh::setPrimitive(GLenum primitive)
{
    _primitive = primitive;
}


//---------------------------------------------- Material ---------------------------------------------//
void Mesh::setMaterialAmbient(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
    _materialAmbient[0] = r;
    _materialAmbient[1] = g;
    _materialAmbient[2] = b;
    _materialAmbient[3] = a;
}

void Mesh::setMaterialDiffuse(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
    _materialDiffuse[0] = r;
    _materialDiffuse[1] = g;
    _materialDiffuse[2] = b;
    _materialDiffuse[3] = a;
}

void Mesh::setMaterialSpecular(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
    _materialSpecular[0] = r;
    _materialSpecular[1] = g;
    _materialSpecular[2] = b;
    _materialSpecular[3] = a;
}

void Mesh::setMaterialEmission(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
    _materialEmission[0] = r;
    _materialEmission[1] = g;
    _materialEmission[2] = b;
    _materialEmission[3] = a;
}

void Mesh::setMaterialShininess(GLfloat level)
{
    _materialShininess[0] = level;
}


//----------------------------------------- Lighting --------------------------------------------//
void Mesh::setLightingEnabled(bool enabledDisabled)
{
    _lightingEnabled = enabledDisabled;
}


//------------------------------------------ ArcBall --------------------------------------------//
void Mesh::setArcBall(ArcBall *ab)
{
    _arcBall = ab;
}

void Mesh::setArcBallEnable(bool enableDisable)
{
    _arcBallEnable = enableDisable;
}


//------------------------------------------ General --------------------------------------------//
void Mesh::setHidden(bool hide)
{
    _isHidden = hide;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// UTILITIES /  HELPERS ///////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

//----------------------------------------- Sphere -------------------------------------------//
void Mesh::makeSphere(float radius, float numLongitude, float numLatitude)
{
    _verticies.clear();
    _colors.clear();

    float latitude = 1.0 / (numLatitude-1);
    float longitude = 1.0 / (numLongitude-1);

    //---- Vertex / Normals
    for(int lat = 0; lat < numLatitude; lat++)
    {
        for(int lon = 0; lon < numLongitude; lon++)
        {
            float y = sin( -M_PI_2 + M_PI * lat * latitude );
            float x = cos(2*M_PI * lon * longitude) * sin( M_PI * lat * latitude );
            float z = sin(2*M_PI * lon * longitude) * sin( M_PI * lat * latitude );

            QVector3D point;

            point.setX(x * radius);
            point.setY(y * radius);
            point.setZ(z * radius);

            newVertex(point.x(), point.y(), point.z());

            _normals.append(QVector3D(x,y,z));
        }
    }

    //---- Index
    _indicies.clear();

    for(int lat = 0; lat < numLatitude - 1; lat++)
    {
        for(int lon = 0; lon < numLongitude - 1; lon++)
        {
            _indicies.append( lat * numLongitude + lon);
            _indicies.append(lat * numLongitude + (lon+1));
            _indicies.append((lat+1) * numLongitude + (lon+1));
            _indicies.append((lat+1) * numLongitude + lon);
        }
    }
}

void Mesh::makeCircle(float radius, float numSlices)
{
    _verticies.clear();
    _colors.clear();


    for(int i =0; i <= numSlices*2.0f; i++)
    {
        double angle = 2.0f * M_PI * (float)i / (numSlices*2.0f);
        double x = cos(angle)*radius;
        double y = sin(angle)*radius;
        newVertex(x,y,0);
        _normals.append(QVector3D(x,y,0));
    }

    //initColors();

    //qDebug() << "circle" << _verticies;
}

void Mesh::makeArc(float radius, float degreeStart, float degreeStop, float numSlices)
{
    _verticies.clear();
    _colors.clear();

    float degreeRange = degreeStop - degreeStart;

    for(int i =0; i <= numSlices*2.0f; i++)
    {
        double angle = degreeRange * ( (float)i / (numSlices*2.0f) ) + degreeStart;

        angle *= 0.0174532925;

        double x = cos(angle)*radius;
        double y = sin(angle)*radius;
        newVertex(x,y,0);
        _normals.append(QVector3D(x,y,0));
    }
}


//--------------------------------------- Cylinder -----------------------------------------//
void Mesh::makeCylinder(float radius, float height, float numLongitude, float numLatitude)
{
    _verticies.clear();
    _colors.clear();

    float latitude = 1.0 / (numLatitude);
    float longitude = 1.0 / (numLongitude);

    //---- Vertex / Normals
    for(int lat = 0; lat < numLatitude; lat++)
    {
        for(int lon = 0; lon < numLongitude; lon++)
        {
            float y = lat;
            //float y = sin( -M_PI_2 + M_PI * lat * latitude );
            float x = cos(2*M_PI * (lon) * longitude);// * sin( M_PI * lat * latitude );
            float z = sin(2*M_PI * (lon) * longitude);// * sin( M_PI * lat * latitude );

            QVector3D point;

            point.setX(x * radius);
            point.setY(y * radius);
            point.setZ(z * radius);

            qDebug() << "x" << x << "z" << z;

            newVertex(point.x(), point.y(), point.z());

            //_normals.append(QVector3D(x,y,z));
        }
    }

    //---- Index
    _indicies.clear();

    for(int lat = 0; lat < numLatitude; lat++)
    {
        for(int lon = 0; lon < numLongitude; lon++)
        {
            _indicies.append( lat * numLongitude + lon);
            _indicies.append(lat * numLongitude + (lon+1));
            _indicies.append((lat+1) * numLongitude + (lon+1));
            _indicies.append((lat+1) * numLongitude + lon);
        }
    }
}

void Mesh::makeCylinder(float radius, QVector3D start, QVector3D end, float numLongitude, float numLatitude)
{
    //---- Create the verticies
    _verticies.clear();
    _normals.clear();

    QVector3D diff = start - end;
    QVector3D cross = QVector3D::crossProduct(diff, QVector3D(0,1,0));
    float angle = angle = 180 / M_PI * acos ((QVector3D::dotProduct(QVector3D(0,1,0), diff) / diff.length()));

    float height = diff.length() / numLatitude;

    QMatrix4x4 mat;

    mat.translate(end);
    mat.rotate(-angle, cross);

    //Length divisions
    for(int h = 0; h < numLatitude; h++)
    {
        //Circulat divisions
        for(int s = 0; s < numLongitude; s++)
        {
            QVector3D currentVec = mat * QVector3D( radius*cos( 2*M_PI*s/(numLongitude - 1) ), h*height, radius*sin( 2*M_PI*s/(numLongitude - 1))) ;
            //verticies.append(QVector3D(_radius*cos( 2*M_PI*s/(_numPointsPerSlice - 1) ), h, _radius*sin( 2*M_PI*s/(_numPointsPerSlice - 1) )));
            _verticies.append(currentVec);

            QVector3D normal = QVector3D(1.0*cos( 2*M_PI*s/(numLongitude - 1)), 0, 1.0*sin( 2*M_PI*s/(numLongitude - 1)));
            //normal.normalize();
            _normals.append(normal);
        }
    }

    //---- Index the verticies so we can draw a mesh
    _indicies.clear();

    for(int i = 0; i < numLatitude - 1; i++)
    {
        //If an odd row go one direction (there are alternative ways)
        if(!(i % 2))
        {
            for(int j = 0; j < numLongitude; j++)
            {
                _indicies.append(j+i*numLongitude);
                _indicies.append(j+i*numLongitude + numLongitude);

                //qDebug() << j+i*_height<< j+i*_height + _height;
            }
        }

        //If an even row, go the other direction
        else
        {
            for(int j = numLongitude - 1; j >= 0; j--)
            {
                _indicies.append(j+i*numLongitude);
                _indicies.append(j+i*numLongitude + numLongitude);
                //qDebug() << j+i*_height<< j+i*_height + _height;
            }
        }
    }
}


//--------------------------------------- Plane -----------------------------------------//
void Mesh::makePlane(int rows, int columns)
{
    //---- Verticies
    _verticies.clear();

    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < columns; j++)
        {
            newVertex( i, j, 0);
        }
    }

    //---- Indicies (GL_QUADS)
    setPrimitive(GL_QUADS);
    _indicies.clear();

    for(int i = 0; i < rows - 1; i++)
    {
        for(int j = 0; j < columns - 1; j++)
        {
            _indicies.append(j+i*columns);
            _indicies.append(j+i*columns + columns);
            _indicies.append(j+i*columns + columns + 1);
            _indicies.append(j+i*columns + 1);
        }
    }

    //---- Normals
    /*
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < columns; j++)
        {
            QMatrix4x4 mat;
            mat.rotate(-90, 0, 1, 0);

            QVector3D normal = mat * QVector3D( i, j, 0);
            normal.normalize();
            _normals.append(normal);
        }
    }
    */
}

void Mesh::makePlane(int rows, int columns, float unitSize)
{
    //---- Verticies
    _verticies.clear();

    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < columns; j++)
        {
            _verticies.append(QVector3D(i*unitSize,j*unitSize,0));
            //newVertex( i*unitSize, j*unitSize, 0);
        }
    }

    //---- Indicies (GL_QUADS)
    _indicies.clear();

    for(int i = 0; i < rows - 1; i++)
    {
        for(int j = 0; j < columns - 1; j++)
        {
            _indicies.append(j+i*columns);
            _indicies.append(j+i*columns + columns);
            _indicies.append(j+i*columns + columns + 1);
            _indicies.append(j+i*columns + 1);
        }
    }

    initColors();

    //---- Normals
    /*
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < columns; j++)
        {
            QMatrix4x4 mat;
            mat.rotate(-90, 0, 1, 0);

            QVector3D normal = mat * QVector3D( i, j, 0);
            normal.normalize();
            _normals.append(normal);
        }
    }
    */
}


//--------------------------------------- Cone -----------------------------------------//
void Mesh::makeCone(float radius, float height, float numSlices)
{

    //Use triangles primitive
    setPrimitive(GL_TRIANGLES);

    _verticies.clear();
    _colors.clear();

    //Base
    for(int i = 0; i < numSlices*2; i++)
    {

        float theta = M_PI_2 * (float)(i / numSlices*2);
        float y = sinf(theta);
        float x = cosf(theta);
        float z = 0;

        QVector3D point;

        point.setX(x * radius);
        point.setY(y * radius);
        point.setZ(z * radius);

        newVertex(point.x(), point.y(), point.z());

        _normals.append(QVector3D(x,y,z));
    }

    //Point
    newVertex(0, 0, -height);
    _normals.append(QVector3D(0,0,-height));


    //---- Index
    _indicies.clear();

    for(int i = 0; i < numSlices*2; i++)
    {
        if(i == numSlices*2 - 1)
        {
            //Connect first and last
            _indicies.append(i);
            _indicies.append(0);
            _indicies.append(_verticies.size() - 1);
        }
        else
        {
            _indicies.append(i);
            _indicies.append(i + 1);
            _indicies.append(_verticies.size() - 1);
        }


    }
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////// DRAWING //////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
void Mesh::drawMesh()
{
    if(!_isHidden)
    {
        glPolygonMode(_face, _mode);

        //Push Matrix
        glPushMatrix();

        glMultMatrixf(_transformationMatrix.data());

        //Enable vertex array drawing
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_COLOR_ARRAY);
        glEnableClientState(GL_NORMAL_ARRAY);

        //Send our arrays to open gl
        glVertexPointer(3, GL_FLOAT, 0, _verticies.constData());
        glNormalPointer(GL_FLOAT, 0, _normals.constData());
        glColorPointer(4, GL_FLOAT, 0, _colors.constData());

        //Draw our verticies and colors
        glDrawElements(_primitive, _indicies.size(), GL_UNSIGNED_SHORT, _indicies.constData());

        //Disable Vertex array drawing
        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_COLOR_ARRAY);
        glDisableClientState(GL_NORMAL_ARRAY);

        //Pop
        glPopMatrix();
    }
}

void Mesh::drawFaces()
{
    _mode = GL_FILL;
    _primitive = GL_TRIANGLES;

    if(!_isHidden)
    {
        //Push Matrix
        glPushMatrix();

        glPolygonMode(_face, _mode);

        glPolygonOffset(3, 3);
        glEnable(GL_POLYGON_OFFSET_FILL);

        glMultMatrixf(_transformationMatrix.data());

        //Enable vertex array drawing
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_COLOR_ARRAY);
        glEnableClientState(GL_NORMAL_ARRAY);

        //Send our arrays to open gl
        glVertexPointer(3, GL_FLOAT, 0, _verticies.constData());
        glNormalPointer(GL_FLOAT, 0, _normals.constData());
        glColorPointer(4, GL_FLOAT, 0, _colors.constData());

        //Draw our verticies and colors
        glDrawElements(_primitive, _indicies.size(), GL_UNSIGNED_SHORT, _indicies.constData());

        glDisable(GL_POLYGON_OFFSET_FILL);

        //Disable Vertex array drawing
        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_COLOR_ARRAY);
        glDisableClientState(GL_NORMAL_ARRAY);

        //Pop
        glPopMatrix();
    }
}

void Mesh::drawWireframe()
{
    _mode = GL_LINE;
    _primitive = GL_TRIANGLES;

    if(!_isHidden)
    {
        glPolygonMode(_face, _mode);

        //Push Matrix
        glPushMatrix();

        glMultMatrixf(_transformationMatrix.data());

        //Enable vertex array drawing
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_COLOR_ARRAY);
        glEnableClientState(GL_NORMAL_ARRAY);

        //Send our arrays to open gl
        glVertexPointer(3, GL_FLOAT, 0, _verticies.constData());
        glNormalPointer(GL_FLOAT, 0, _normals.constData());
        glColorPointer(4, GL_FLOAT, 0, _colors.constData());

        //Draw our verticies and colors
        glDrawElements(_primitive, _indicies.size(), GL_UNSIGNED_SHORT, _indicies.constData());

        //Disable Vertex array drawing
        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_COLOR_ARRAY);
        glDisableClientState(GL_NORMAL_ARRAY);

        //Pop
        glPopMatrix();
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////// COLOR ///////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
void Mesh::setColor(float r, float g, float b)
{
    _colors.clear();

    for(int i = 0; i < _verticies.size(); i++)
    {
        _colors.append(QVector4D(r,g,b,1.0));
    }
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////// UTILS ///////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
QVector3D Mesh::getMeshCenter()
{
    QVector3D min, max;

    min = max = _verticies.at(0);

    for(int i = 0; i < _verticies.size(); i++)
    {
        //---- Min
        //x
        if(min.x() > _verticies.at(i).x())
        {
            min.setX(_verticies.at(i).x());
        }

        //y
        if(min.y() > _verticies.at(i).y())
        {
            min.setY(_verticies.at(i).y());
        }

        //z
        if(min.z() > _verticies.at(i).z())
        {
            min.setZ(_verticies.at(i).z());
        }

        //---- Max
        //x
        if(max.x() < _verticies.at(i).x())
        {
            max.setX(_verticies.at(i).x());
        }
        //y
        if(max.y() < _verticies.at(i).y())
        {
            max.setY(_verticies.at(i).y());
        }

        //z
        if(max.z() < _verticies.at(i).z())
        {
            max.setZ(_verticies.at(i).z());
        }
    }

    //qDebug() << "minmax center" << min << max << (min + max)/2.0;

    return (min + max)/2.0f;
}

void Mesh::clear()
{
    _verticies.clear();
    _normals.clear();
    _colors.clear();
}
