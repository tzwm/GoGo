#ifndef __STONE_ITEM_H__
#define __STONE_ITEM_H__

#include <QGraphicsItem>
#include <QPainter>

class StoneItem : public QGraphicsItem
{
public:
    StoneItem(char _color);

    virtual QRectF boundingRect() const;
    virtual QPainterPath shape() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    char stoneColor;
    int stoneSize;
};


#endif

