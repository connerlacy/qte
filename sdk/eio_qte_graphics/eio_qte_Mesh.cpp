#include "eio_qte_Mesh.h"

Mesh::Mesh() :
    _face(GL_FRONT_AND_BACK),
    _mode(GL_LINE),
    _primitive(GL_FILL),
    m_IndexBuffer(QOpenGLBuffer::IndexBuffer)
{

    glClearColor(0, 0, 0, 1);
}

void Mesh::newVertex(float x, float y, float z)
{
    _vertices.append(QVector3D(x,y,z));

    //initIndicies();
}

void Mesh::initIndicies()
{
    _indices.clear();

    for(int i = 0; i < _vertices.size(); i++)
    {
        _indices.append(i);
    }
}

void Mesh::setMultMatrix(QMatrix4x4 mtrx)
{
    _transformationMatrix = mtrx;
}

void Mesh::setPolygonMode(GLenum face, GLenum mode)
{
    _face = face;
    _mode = mode;
}

void Mesh::setPrimitive(GLenum primitive)
{
    _primitive = primitive;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// UTILITIES /  HELPERS ///////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

//----------------------------------------- Sphere -------------------------------------------//
void Mesh::makeSphere(float radius, float numLongitude, float numLatitude)
{
    setPrimitive(GL_QUADS);

    _vertices.clear();
    _colors.clear();

    //radius = 0.01;

    float latitude = 1.0 / float(numLatitude-1);
    float longitude = 1.0 / float(numLongitude-1);

    //---- Vertex / Normals
    for(float lat = 0; lat < numLatitude; lat++)
    {
        for(float lon = 0; lon < numLongitude; lon++)
        {
            float y = sin( -M_PI_2 + M_PI * lat * latitude );
            float x = cos(2.0f*M_PI * lon * longitude) * sin( M_PI * lat * latitude );
            float z = sin(2.0f*M_PI * lon * longitude) * sin( M_PI * lat * latitude );

            QVector3D point;

            point.setX(x * radius);
            point.setY(y * radius);
            point.setZ(z * radius);

            newVertex(point.x(), point.y(), point.z());

            _normals.append(QVector3D(x,y,z));
        }
    }

    //---- Index
    _indices.clear();

    for(int lat = 0; lat < numLatitude - 1; lat++)
    {
        for(int lon = 0; lon < numLongitude - 1; lon++)
        {
            _indices.append( lat * numLongitude + lon);
            _indices.append(lat * numLongitude + (lon+1));
            _indices.append((lat+1) * numLongitude + (lon+1));
            _indices.append((lat+1) * numLongitude + lon);
        }
    }
}


//----------------------------------------- Circle -------------------------------------------//
void Mesh::makeCircle(float radius, float numSlices)
{
    _vertices.clear();
    _colors.clear();


    for(int i = 0; i < numSlices*2.0f; i++)
    {
        double angle = 2.0f * M_PI * (float)i / (numSlices*2.0f);
        double x = cos(angle)*radius;
        double y = sin(angle)*radius;
        newVertex(x,y,0);
        _normals.append(QVector3D(x,y,0));
    }

    _indices.clear();

    for(int i = 0; i < _vertices.size(); i++)
    {
        _indices.append(i);
    }

    //initColors();

    //qDebug() << "circle" << _vertices;
}

void Mesh::makeCircle(float radius, float borderWidth, float numSlices)
{
    //Arrange in groups of
    _vertices.clear();
    _colors.clear();


    float degreeRange = 360;

    //Inner Arc
    for(int i = 0; i <= numSlices*2; i++)
    {
        double angle = degreeRange * ( (float)i / (numSlices*2.0f) );

        angle *= 0.0174532925;

        //Inner
        double xInner = cos(angle)*radius;
        double yInner = sin(angle)*radius;
        newVertex(xInner,yInner,0);
        _normals.append(QVector3D(xInner,yInner,0));

        //Outer
        double xOuter = cos(angle)*(radius + borderWidth);
        double yOuter = sin(angle)*(radius + borderWidth);
        newVertex(xOuter,yOuter,0);
        _normals.append(QVector3D(xOuter,yOuter,0));

    }

    _indices.clear();

    //Index
    for(int i = 0; i < _vertices.size() - 2; i += 2)
    {
        //Triangle 1
        _indices.append(i);
        _indices.append(i + 1);
        _indices.append(i + 3);

        //Triangle 2
        _indices.append(i);
        _indices.append(i + 2);
        _indices.append(i + 3);
    }

}


//----------------------------------------- Arc -------------------------------------------//
void Mesh::makeArc(float radius, float width, float degreeStart, float degreeStop, float numSlices)
{
    //Arrange in groups of
    _vertices.clear();
    _colors.clear();


    float degreeRange = degreeStop - degreeStart;


    //Inner Arc
    for(int i = 0; i <= numSlices*2; i++)
    {
        double angle = degreeRange * ( (float)i / (numSlices*2.0f) ) + degreeStart;

        angle *= 0.0174532925;

        //Inner
        double xInner = cos(angle)*radius;
        double yInner = sin(angle)*radius;
        newVertex(xInner,yInner,0);
        _normals.append(QVector3D(xInner,yInner,0));

        //Outer
        double xOuter = cos(angle)*(radius + width);
        double yOuter = sin(angle)*(radius + width);
        newVertex(xOuter,yOuter,0);
        _normals.append(QVector3D(xOuter,yOuter,0));

    }

    _indices.clear();

    //Index
    for(int i = 0; i < _vertices.size() - 2; i += 2)
    {
        //Triangle 1
        _indices.append(i);
        _indices.append(i + 1);
        _indices.append(i + 3);

        //Triangle 2
        _indices.append(i);
        _indices.append(i + 2);
        _indices.append(i + 3);
    }

    /*
    //Outer Arc
    for(int i = 0; i < numSlices*2.0f; i++)
    {
        double angle = degreeRange * ( (float)i / (numSlices*2.0f) ) + degreeStart;

        angle *= 0.0174532925;

        double x = cos(angle)*(radius + width);
        double y = sin(angle)*(radius + width);
        newVertex(x,y,0);
        _normals.append(QVector3D(x,y,0));
    }

    qDebug() << "arc vertices" << _verticies.size();

    _indicies.clear();

    for(int i = _verticies.size() - 1; i >= numSlices*2.0f ; i--)
    {
        _indicies.append( i );
    }

    for(int i = 0; i < numSlices*2.0f; i++)
    {
        _indicies.append( i );
    }


    for(int i = _verticies.size()/2; i < numSlices*2.0f; i++)
    {
        //_indicies.append(i);
    }

    //_indicies.append(_verticies.size() - 1);
    */

}


//--------------------------------------- Cylinder -----------------------------------------//
void Mesh::makeCylinder(float radius, float height, float numLongitude, float numLatitude)
{
    _vertices.clear();
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

            //qDebug() << "x" << x << "z" << z;

            newVertex(point.x(), point.y(), point.z());

            //_normals.append(QVector3D(x,y,z));
        }
    }

    //---- Index
    _indices.clear();

    for(int lat = 0; lat < numLatitude; lat++)
    {
        for(int lon = 0; lon < numLongitude; lon++)
        {
            _indices.append( lat * numLongitude + lon);
            _indices.append(lat * numLongitude + (lon+1));
            _indices.append((lat+1) * numLongitude + (lon+1));
            _indices.append((lat+1) * numLongitude + lon);
        }
    }
}

void Mesh::makeCylinder(float radius, QVector3D start, QVector3D end, float numLongitude, float numLatitude)
{
    //---- Create the vertices
    _vertices.clear();
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
            //vertices.append(QVector3D(_radius*cos( 2*M_PI*s/(_numPointsPerSlice - 1) ), h, _radius*sin( 2*M_PI*s/(_numPointsPerSlice - 1) )));
            _vertices.append(currentVec);

            QVector3D normal = QVector3D(1.0*cos( 2*M_PI*s/(numLongitude - 1)), 0, 1.0*sin( 2*M_PI*s/(numLongitude - 1)));
            //normal.normalize();
            _normals.append(normal);
        }
    }

    //---- Index the vertices so we can draw a mesh
    _indices.clear();

    for(int i = 0; i < numLatitude - 1; i++)
    {
        //If an odd row go one direction (there are alternative ways)
        if(!(i % 2))
        {
            for(int j = 0; j < numLongitude; j++)
            {
                _indices.append(j+i*numLongitude);
                _indices.append(j+i*numLongitude + numLongitude);

                //qDebug() << j+i*_height<< j+i*_height + _height;
            }
        }

        //If an even row, go the other direction
        else
        {
            for(int j = numLongitude - 1; j >= 0; j--)
            {
                _indices.append(j+i*numLongitude);
                _indices.append(j+i*numLongitude + numLongitude);
                //qDebug() << j+i*_height<< j+i*_height + _height;
            }
        }
    }
}


//--------------------------------------- Plane -----------------------------------------//
void Mesh::makePlane(int rows, int columns)
{

    //---- Verticies
    _vertices.clear();

    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < columns; j++)
        {
            newVertex( i, j, 0);
        }
    }

    _vertices.clear();

    for(int x = 0; x < rows - 1; x++)
    {
        //Even Row
        if ( (x & 1) == 0 )
        {
            for(int y = 0; y < columns - 1; y++)
            {
                if((y & 1) == 0)
                {
                    //Triangle 1
                    newVertex(x, y, 0);
                    newVertex(x, y + 1, 0);
                    newVertex(x + 1, y, 0);

                    //Triangle 2
                    newVertex((x + 1), y,0);
                    newVertex((x + 1), y + 1,0);
                    newVertex(x, y + 1,0);
                }
                else
                {
                    //Triangle 1
                    newVertex(x, y, 0);
                    newVertex((x + 1), y, 0);
                    newVertex((x + 1), y + 1, 0);

                    //Triangle 2
                    newVertex(x, y, 0);
                    newVertex((x + 1), y + 1, 0);
                    newVertex(x, y + 1, 0);
                }
            }
        }

        //Odd Rows
        else
        {
            for(int y = 0; y < columns - 1; y++)
            {
                if((y & 1) == 1)
                {
                    //Triangle 1
                    newVertex(x, y, 0);
                    newVertex(x, y + 1, 0);
                    newVertex((x + 1), y, 0);

                    //Triangle 2
                    newVertex((x + 1), y, 0);
                    newVertex((x + 1), y + 1, 0);
                    newVertex(x, y + 1, 0);
                }
                else
                {
                    //Triangle 1
                    newVertex(x, y, 0);
                    newVertex((x + 1), y, 0);
                    newVertex((x + 1), y + 1, 0);

                    //Triangle 2
                    newVertex(x, y, 0);
                    newVertex((x + 1), y + 1, 0);
                    newVertex(x, y + 1, 0);

                }
            }
        }
    }

    _indices.clear();

    for(int i = 0; i < _vertices.size(); i++)
    {
        _indices.append(i);
    }

    /*
    _indices.clear();

    for(int x = 0; x < rows - 1; x++)
    {
        //Even Row
        if ( (x & 1) == 0 )
        {
            for(int y = 0; y < columns - 1; y++)
            {
                if((y & 1) == 0)
                {
                    //Triangle 1
                    _indices.append(x * columns + y);
                    _indices.append(x * columns + y + 1);
                    _indices.append((x + 1) * columns + y);

                    //Triangle 2
                    _indices.append((x + 1) * columns + y);
                    _indices.append((x + 1) * columns + y + 1);
                    _indices.append(x * columns + y + 1);
                }
                else
                {
                    //Triangle 1
                    _indices.append(x * columns + y);
                    _indices.append((x + 1) * columns + y);
                    _indices.append((x + 1) * columns + y + 1);

                    //Triangle 2
                    _indices.append(x * columns + y);
                    _indices.append((x + 1) * columns + y + 1);
                    _indices.append(x * columns + y + 1);

                }
            }
        }

        //Odd Rows
        else
        {
            for(int y = 0; y < columns - 1; y++)
            {
                if((y & 1) == 1)
                {
                    //Triangle 1
                    _indices.append(x * columns + y);
                    _indices.append(x * columns + y + 1);
                    _indices.append((x + 1) * columns + y);

                    //Triangle 2
                    _indices.append((x + 1) * columns + y);
                    _indices.append((x + 1) * columns + y + 1);
                    _indices.append(x * columns + y + 1);
                }
                else
                {
                    //Triangle 1
                    _indices.append(x * columns + y);
                    _indices.append((x + 1) * columns + y);
                    _indices.append((x + 1) * columns + y + 1);

                    //Triangle 2
                    _indices.append(x * columns + y);
                    _indices.append((x + 1) * columns + y + 1);
                    _indices.append(x * columns + y + 1);

                }
            }
        }
    }
    */

    //m_IndexBuffer.bind();
    //m_IndexBuffer.allocate(_indices.constData(), _indices.size() * sizeof(GLushort));

    /*
    //---- Normals

    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < columns; j++)
        {
            QMatrix4x4 mat;
            mat.rotate(90, 0, 1, 0);

            QVector3D normal = mat * QVector3D( i, j, 0);
            normal.normalize();
            _normals.append(normal);
        }
    }
    */

    //initCubeGeometry();

}

void Mesh::makePlane(int rows, int columns, float unitSize)
{
    setPrimitive(GL_QUADS);

    //---- Verticies
    _vertices.clear();

    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < columns; j++)
        {
            _vertices.append(QVector3D(i*unitSize,j*unitSize,0));
            //newVertex( i*unitSize, j*unitSize, 0);
        }
    }

    //---- Indicies (GL_QUADS)
    _indices.clear();

    for(int i = 0; i < rows - 1; i++)
    {
        for(int j = 0; j < columns - 1; j++)
        {
            _indices.append(j+i*columns);
            _indices.append(j+i*columns + columns);
            _indices.append(j+i*columns + columns + 1);
            _indices.append(j+i*columns + 1);
        }
    }

    //---- Normals
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < columns; j++)
        {
            QMatrix4x4 mat;
            mat.rotate(90, 0, 1, 0);

            QVector3D normal = mat * QVector3D( i, j, 0);
            normal.normalize();
            _normals.append(normal);
        }
    }

}


//--------------------------------------- Cone -----------------------------------------//
void Mesh::makeCone(float radius, float height, float numSlices)
{

    //Use triangles primitive
    setPrimitive(GL_TRIANGLES);

    _vertices.clear();
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
    _indices.clear();

    for(int i = 0; i < numSlices*2; i++)
    {
        if(i == numSlices*2 - 1)
        {
            //Connect first and last
            _indices.append(i);
            _indices.append(0);
            _indices.append(_vertices.size() - 1);
        }
        else
        {
            _indices.append(i);
            _indices.append(i + 1);
            _indices.append(_vertices.size() - 1);
        }
    }
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////// DRAWING //////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

void Mesh::createBuffers()
{
    //---- Position
    m_PositionBuffer.create();
    m_PositionBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_PositionBuffer.bind();
    m_PositionBuffer.allocate(_vertices.constData(), _vertices.size() * sizeof(QVector3D));

    //---- Normals
    m_NormalBuffer.create();
    m_NormalBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_NormalBuffer.bind();
    m_NormalBuffer.allocate(_normals.constData(), _normals.size() * sizeof(QVector3D));

    //---- Indices
    m_IndexBuffer.create();
    m_IndexBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_IndexBuffer.bind();
    m_IndexBuffer.allocate(_indices.constData(), _indices.size() * sizeof(GLushort));

    for(float i = 0 ; i < _vertices.size()/3; i++)
    {
        QVector4D col = QVector4D(float(qrand())/float(RAND_MAX),float(qrand())/float(RAND_MAX),float(qrand())/float(RAND_MAX), 1);
        _colors.append(col);
        _colors.append(col);
        _colors.append(col);
        //qDebug() << "i/float(_vertices.size())" << RAND_MAX;
    }


    //---- Color
    m_ColorBuffer.create();
    m_ColorBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_ColorBuffer.bind();
    m_ColorBuffer.allocate( _colors.constData(), _colors.size() * sizeof(QVector4D) );
}

void Mesh::drawMesh()
{
    glPolygonMode(_face, _mode);
    glDrawElements(_primitive, _indices.size(), GL_UNSIGNED_SHORT, 0);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////// UTILS ///////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
QVector3D Mesh::getMeshCenter()
{
    QVector3D min, max;

    min = max = _vertices.at(0);

    for(int i = 0; i < _vertices.size(); i++)
    {
        //---- Min
        //x
        if(min.x() > _vertices.at(i).x())
        {
            min.setX(_vertices.at(i).x());
        }

        //y
        if(min.y() > _vertices.at(i).y())
        {
            min.setY(_vertices.at(i).y());
        }

        //z
        if(min.z() > _vertices.at(i).z())
        {
            min.setZ(_vertices.at(i).z());
        }

        //---- Max
        //x
        if(max.x() < _vertices.at(i).x())
        {
            max.setX(_vertices.at(i).x());
        }
        //y
        if(max.y() < _vertices.at(i).y())
        {
            max.setY(_vertices.at(i).y());
        }

        //z
        if(max.z() < _vertices.at(i).z())
        {
            max.setZ(_vertices.at(i).z());
        }
    }

    //qDebug() << "minmax center" << min << max << (min + max)/2.0;

    return (min + max)/2.0f;
}

void Mesh::clear()
{
    _vertices.clear();
    _normals.clear();
    _colors.clear();
}
