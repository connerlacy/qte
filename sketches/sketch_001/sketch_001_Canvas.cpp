#include "sketch_001_Canvas.h"

void sketch_001_Canvas::setup()
{
    TWOD = 1;


    //m_Interval = 1000;

    for(double w = 0; w < 10; w++)
    {
        for(double h = 0.0; h < 10; h++)
        {
            double value = (myModule.GetValue (w, h, 0.5) + 1.0) / 2.0;
            qDebug() << w << h << value;
        }
    }

    myModule.SetOctaveCount(2);
    m_Interval = 50;



    //pixmap = new QPixmap(size());
}

void sketch_001_Canvas::draw()
{
    m_Time += m_Interval;

    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, true);
    p.setPen(QColor("white"));
    p.setBrush(QColor(255, 249, 207));
    p.fillRect(0,0,this->width(), this->height(), p.brush());

    double size = this->width()/20.0;

    for(double w = 0; w < this->width() + size; w+= size / 10.0)
    {
        for(double o = 0; o < 10.0; o += 2.0)
        {
            double value0 = (myModule.GetValue (w/this->width()*2.0, o, double(m_Time*0.00005)) / 2.0) + 0.5;

            value0 *= 1.0;

            QColor col1, col2;


            if(value0 < 0.0)
            {
                col1 = QColor(0.0, 105.0, 100.0, 255);
                col2 = QColor(0.0, 5.0, 100.0, 255);
            }

            else if(value0 > 1.0)
            {
                col1 = QColor(50.0, 50.0 + 105.0, 50.0 + 100.0, 255);
                col2 = QColor(200, 50.0 + 5.0, 50.0 + 100.0, 255);
            }
            else
            {
                col1 = QColor(50*value0, value0 * 50.0 + 105.0, value0 *50.0 + 100.0, 255);
                col2 = QColor(200*value0, value0 * 50.0 + 5.0, value0 *50.0 + 100.0, 255);
            }



            QPen pen;
            pen.setColor(col2);
            pen.setWidth(1);

            p.setPen(pen);
            p.setBrush(col1);

            p.drawEllipse(int(w) - size, this->height()*(value0), size, size);



        }
    }


    //m_drawTimer->stop();
}
