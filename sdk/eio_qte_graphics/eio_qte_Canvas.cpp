#include "eio_qte_Canvas.h"

Canvas::Canvas(QWidget *parent) :
    //QOpenGLWindow(QOpenGLWindow::PartialUpdateBlit, 0)
        QOpenGLWidget(parent)
{
    installEventFilter(this);

    m_ArcBall = new ArcBall(this);

    m_drawTimer = new QTimer;
    m_Interval = 50;
    connect(m_drawTimer, SIGNAL(timeout()), this, SLOT(update()));

    m_ClearColor = QVector4D(0.2,0.2,0.2,1.0);

    // Prevent automatic gl clearing
    //this->setUpdateBehavior(QOpenGLWidget::PartialUpdate);
}

void Canvas::initializeGL()
{
    makeCurrent();

    initializeOpenGLFunctions();
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_LINE_SMOOTH);

    setup();

    m_drawTimer->start(m_Interval);
    m_ArcBall->translate(0,0,15);


}

void Canvas::resizeGL(int width, int height)
{
    //Update arc ball mouse controll
    m_ArcBall->setSize(width, height);

    // Calculate aspect ratio
    qreal aspect = qreal(width) / qreal(height ? height : 1);

    // Set near plane to 3.0, far plane to 7.0, field of view 45 degrees
    const qreal zNear = 0.01, zFar = 2000, fov = 45.0;

    // Reset projection
    m_ProjectionMatrix.setToIdentity();

    // Set perspective projection
    m_ProjectionMatrix.perspective(fov, aspect, zNear, zFar);
}

void Canvas::paintGL()
{
    if(!TWOD)
    {
        glClearColor(m_ClearColor.x(),m_ClearColor.y(),m_ClearColor.z(),m_ClearColor.w());
        glEnable (GL_BLEND);
        glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    GLint faces[6][4] = {  /* Vertex indices for the 6 faces of a cube. */
      {0, 1, 2, 3}, {3, 2, 6, 7}, {7, 6, 5, 4},
      {4, 5, 1, 0}, {5, 6, 2, 1}, {7, 4, 0, 3} };
    GLfloat v[8][3];  /* Will be filled in with X,Y,Z vertexes. */
    GLfloat n[6][3] = {  /* Normals for the 6 faces of a cube. */
      {-1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {1.0, 0.0, 0.0},
      {0.0, -1.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, -1.0} };

    for (int i = 0; i < 6; i++)
    {
      glBegin(GL_QUADS);
      glNormal3fv(&n[i][0]);
      glVertex3fv(&v[faces[i][0]][0]);
      glVertex3fv(&v[faces[i][1]][0]);
      glVertex3fv(&v[faces[i][2]][0]);
      glVertex3fv(&v[faces[i][3]][0]);
      glEnd();
    }

    //qDebug() << "draw";

    draw();
}


//------------------------------------------ MOUSE ------------------------------------------//
void Canvas::mouseMoveEvent(QMouseEvent *me)
{
    m_ArcBall->drag(me->x(), me->y());
    //qDebug() << "mouse";
}

void Canvas::mousePressEvent(QMouseEvent *me)
{
    //this->setFocus();
    m_ArcBall->click(me->x(), me->y());
}

void Canvas::mouseReleaseEvent(QMouseEvent *me)
{
    m_ArcBall->drag(me->x(), me->y());
}

//------------------------------------------ EVENTS ------------------------------------------//
bool Canvas::eventFilter(QObject *obj, QEvent *e)
{
    //------------- KEYS
    if(e->type() == QEvent::KeyPress)
    {
        QKeyEvent *ke = static_cast<QKeyEvent *>(e);

        if(ke->key() == Qt::Key_Up)
        {
            m_ArcBall->_translateY+= 0.1;
        }
        else if(ke->key() == Qt::Key_Down)
        {
            m_ArcBall->_translateY-= 0.1;

        }
        else if(ke->key() == Qt::Key_Left)
        {
            m_ArcBall->_translateX-= 0.1;

        }
        else if(ke->key() == Qt::Key_Right)
        {
            m_ArcBall->_translateX+= 0.1;

        }
        else if(ke->key() == Qt::Key_O)
        {
            m_ArcBall->_translateZ+= 0.5;

        }
        else if(ke->key() == Qt::Key_I)
        {
            m_ArcBall->_translateZ-= 0.5;

        }
        else
        {
            return QObject::eventFilter(obj, e);
        }

        m_ArcBall->updateMatrix();
        return true;
    }

    //------------- Mouse
    else if(e->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent *me = static_cast<QMouseEvent *>(e);
        //this->setFocus();
        m_ArcBall->click(me->x(), me->y());
    }
    else if(e->type() == QEvent::MouseButtonRelease)
    {
        QMouseEvent *me = static_cast<QMouseEvent *>(e);
        m_ArcBall->drag(me->x(), me->y());
    }
    else if(e->type() == QEvent::MouseMove)
    {
        QMouseEvent *me = static_cast<QMouseEvent *>(e);
        m_ArcBall->drag(me->x(), me->y());
    }

    return QObject::eventFilter(obj, e);
}

void Canvas::setClearColor(float r, float g, float b, float a)
{
    m_ClearColor = QVector4D(r,g,b,a);
}
