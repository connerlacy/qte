#include "eio_qte_Canvas.h"

Canvas::Canvas(QWidget *parent) :
    QOpenGLWidget(parent)
{
    //Enable multisampling
    QSurfaceFormat surfaceFormat;
    surfaceFormat.setSamples(16);
    this->setFormat(surfaceFormat);

    //setUpdatesEnabled(false);

    installEventFilter(this);

    m_ArcBall = new ArcBall(this);

    m_drawTimer = new QTimer;
    m_Interval = 50;
    connect(m_drawTimer, SIGNAL(timeout()), this, SLOT(update()));

    m_ClearColor = QVector4D(0.2,0.2,0.2,1);
}

void Canvas::initializeGL()
{
    initializeOpenGLFunctions();

    makeCurrent();
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);

    setup();
    m_drawTimer->start(m_Interval);
    m_ArcBall->translate(0,0,20);

    qDebug() << "initialize GL";
}

void Canvas::resizeGL(int width, int height)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.01f, 2000.0f);

    m_ArcBall->setSize(width, height);
}

void Canvas::paintGL()
{
    makeCurrent();

    glClearColor(m_ClearColor.x(),m_ClearColor.y(),m_ClearColor.z(),m_ClearColor.w());

    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);

    //glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0,0,this->width(), this->height());
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_LIGHT0);

    glPushMatrix();
    glTranslatef(0,0,-3);
    glMultMatrixf(m_ArcBall->_matrix.data());

    GLfloat global_ambient[] = { 1, 1, 1, 1 };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);

    GLfloat specular[] = {0.2f, 0.2f, 0.2f, 1};
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

    GLfloat ambient[] = { 0.5f, 0.5f, 0.5f, 1 };
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);

    GLfloat diffuse[] = { 0.5f, 0.5f, 0.5f };
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);

    GLfloat position[] = { 0, 50, 50, 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, position);

    glLightf (GL_LIGHT0, GL_SPOT_CUTOFF, 90.f);

    glLightf(GL_LIGHT0, GL_SHININESS, 128);

    draw();
    glPopMatrix();
}


//------------------------------------------ MOUSE ------------------------------------------//
void Canvas::mouseMoveEvent(QMouseEvent *me)
{
    m_ArcBall->drag(me->x(), me->y());
}

void Canvas::mousePressEvent(QMouseEvent *me)
{
    this->setFocus();
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
            m_ArcBall->_translateZ+= 0.1;

        }
        else if(ke->key() == Qt::Key_I)
        {
            m_ArcBall->_translateZ-= 0.1;

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
        this->setFocus();
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

