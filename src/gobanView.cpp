#include "gobanView.h"

int GobanView::sizeGrid = 32;

GobanView::GobanView(QWidget* parent) : QGraphicsView(parent)
{
    this->setFixedSize(sizeGrid*20+4, sizeGrid*20+4);
    move(QPoint(300, 50));

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

    for(int i=0;i<19;i++)
        for(int j=0;j<19;j++)
            gobanCur[i][j] = NULL;
}

void GobanView::setGoban(Goban* _goban)
{
    this->goban = _goban;
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

    //Draw star
    int tmp[3] = {3, 9, 15};
    painter->setBrush(Qt::black);
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
        {
            painter->drawEllipse(Helper::toCoord(QPoint(tmp[i], tmp[j]), sizeGrid), 4, 4);
        }
}

void GobanView::mousePressEvent(QMouseEvent* event)
{
    QPoint point = Helper::toPoint(QPoint(event->x(), event->y()), this->sizeGrid);
    if(point.x()<0 || point.x()>18)
        return;
    if(point.y()<0 || point.y()>18)
        return;

    if(!goban->canPlay(point))
        return;

    StoneItem *stone = new StoneItem(goban->getNumCurrent() % 2, point, goban->getNumCurrent()+1);
    stone->setPos(Helper::toCoord(stone->getStonePos(), sizeGrid));
    goban->play(point, stone);
    this->redraw();

    //goban->genPlay();
    //this->redraw();
}

void GobanView::redraw()
{
    for(int i=0;i<19;i++)
        for(int j=0;j<19;j++)
        {
            StoneItem *stone = goban->getStoneOnGoban(i, j);
            if(!stone)
            {
                if(gobanCur[i][j])
                {
                    scene->removeItem(gobanCur[i][j]);
                    gobanCur[i][j] = NULL;
                }
                continue;
            }
            if(!gobanCur[i][j])
            {
                scene->addItem(stone); 
                gobanCur[i][j] = stone;
            }
        }
}
