#include "stoneItem.h"

StoneItem::StoneItem(int _color, const QPoint& _stonePos, int _stoneNum)
{
    stoneColor = _color;
    stoneSize = 30;
    stonePos = _stonePos;
    stoneNum = _stoneNum;
    dead = false;
}


QRectF StoneItem::boundingRect() const
{
    return QRectF(-stoneSize/2, -stoneSize/2, stoneSize, stoneSize);
}

QPainterPath StoneItem::shape() const
{
    QPainterPath path;
    path.addEllipse(QPoint(0, 0), stoneSize/2, stoneSize/2);
    return path;
}

void StoneItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(stoneColor)
    {
        painter->setBrush(Qt::white);
        painter->setPen(Qt::white);
    }
    else
    {
        painter->setBrush(Qt::black);
        painter->setPen(Qt::black);
    }

    painter->drawEllipse(QPoint(0, 0), stoneSize/2, stoneSize/2);
    
    if(stoneColor)
        painter->setPen(Qt::black);
    else
        painter->setPen(Qt::white);
    painter->drawText(-7, 4, QString::number(stoneNum));
}

const QPoint& StoneItem::getStonePos()
{   
    return this->stonePos;
}

void StoneItem::setDead()
{
    dead = true;
}

