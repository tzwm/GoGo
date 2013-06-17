#ifndef __STONE_ITEM_H__
#define __STONE_ITEM_H__

#include <QGraphicsItem>
#include <QPainter>
#include <QPoint>

class StoneItem : public QGraphicsItem
{
public:
    StoneItem(int _color, const QPoint& _stonePos, int _stoneNum);

    virtual QRectF boundingRect() const;
    virtual QPainterPath shape() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    const QPoint& getStonePos();

private:
    int stoneColor;
    int stoneSize;
    QPoint stonePos;
    int stoneNum;
};


#endif

