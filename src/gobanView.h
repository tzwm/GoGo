#ifndef __GOBAN_VIEW_H__
#define __GOBAN_VIEW_H__

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMouseEvent>

#include "helper.h"
#include "stoneItem.h"
#include "goban.h"

class Goban;

class GobanView : public QGraphicsView
{
public:
    GobanView(QWidget* parent = 0);
    ~GobanView();
    void init();
    void setGoban(Goban* _goban);

protected:
    virtual void drawBackground(QPainter* painter, const QRectF &rect);
    virtual void mousePressEvent(QMouseEvent* event);

private:
    QGraphicsScene* scene;
    Goban* goban;    
    StoneItem* gobanCur[19][19];
    int sizeMin;
    int sizeGrid;

    void redraw();
};

#endif

