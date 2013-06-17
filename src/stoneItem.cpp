#include "stoneItem.h"

StoneItem::StoneItem(char _color)
{
    stoneColor = _color;
    stoneSize = 20;
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
    if(stoneColor == 'w')
        painter->setBrush(Qt::white);
    else
        painter->setBrush(Qt::black);
    
    painter->drawEllipse(QPoint(0, 0), stoneSize/2, stoneSize/2);
}

