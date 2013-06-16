#include "gobanView.h"

GobanView::GobanView(QWidget* parent) : QGraphicsView(parent)
{
    sizeGrid = 32;
    this->setFixedSize(sizeGrid*20+4, sizeGrid*20+4);

    scene = new QGraphicsScene();
    scene->setSceneRect(-sizeGrid*20/2, -sizeGrid*20/2, sizeGrid*20, sizeGrid*20);
    this->setScene(scene);

    this->init();
}

GobanView::~GobanView()
{
    //delete scene;
}

void GobanView::init()
{
    this->resize(sizeGrid*20, sizeGrid*20);
    this->sizeMin = sizeGrid*20; 
}


void GobanView::drawBackground(QPainter* painter, const QRectF &rect)
{
    //Draw background
    painter->setBrush(QColor(242, 193, 48));
    painter->setPen(QColor(242, 193, 48));
    painter->drawRect(-this->sizeMin/2, -this->sizeMin/2, this->sizeMin, this->sizeMin);

    //Draw lines
    painter->setPen(Qt::black);
    for(int i = 0; i<19; i++)
    {
        painter->drawLine((-9 + i) * sizeGrid, 1+ (-this->sizeMin/2) +sizeGrid,
                          (-9 + i) * sizeGrid, 1+ (this->sizeMin/2) -sizeGrid);

        painter->drawLine(1+ (-this->sizeMin/2) +sizeGrid, (-9 + i) *sizeGrid,
                          1+ (this->sizeMin/2) -sizeGrid, (-9 + i) *sizeGrid);
    }

    //Draw number
    for(int i = 0; i<19; i++)
    {
        painter->drawText(8 -this->sizeMin/2, (i+1.2)*sizeGrid -this->sizeMin/2, QString::number(i+1));
        painter->drawText(-(19-i+0.1)*sizeGrid + this->sizeMin/2, -15 + this->sizeMin/2, QString(char(i+65)));
    }
}

void GobanView::mousePressEvent(QMouseEvent* event)
{
    scene->clear();
    QPoint point = Helper::toPoint(QPoint(event->x(), event->y()), this->sizeGrid);
    scene->addText(QString::number(event->x())+" "+QString::number(event->y())+" "+
                   QString::number(point.x())+" "+QString::number(point.y()));
}
