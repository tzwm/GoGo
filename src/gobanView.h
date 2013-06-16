#ifndef __GOBAN_VIEW_H__
#define __GOBAN_VIEW_H__

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMouseEvent>

#include "helper.h"

class GobanView : public QGraphicsView
{
public:
    GobanView(QWidget* parent = 0);
    ~GobanView();
    void init();

protected:
    virtual void drawBackground(QPainter* painter, const QRectF &rect);
    virtual void mousePressEvent(QMouseEvent* event);
private:
    QGraphicsScene* scene;
    int sizeMin;
    int sizeGrid;
};

#endif

