#ifndef __GOBAN_H__
#define __GOBAN_H__

#include <vector>
#include <QPoint>

#include "helper.h"
#include "gobanView.h"
#include "stoneItem.h"
#include "controllerGTP.h"

class GobanView;

class Goban 
{
public:
    Goban();
    void setController(Controller_GTP *_con);
    void play(QPoint& pos, StoneItem* stone);
    void addStone(QPoint& pos, StoneItem* stone);
    bool canPlay(QPoint& pos);
    int getNumCurrent();
    StoneItem* getStoneOnGoban(int x, int y);
    StoneItem* getStone(int num);

private:
    GobanView* gobanView;
    Controller_GTP* controller;
    StoneItem* stoneOnGoban[19][19];
    int stone10[19][19];
    std::vector<StoneItem*> stoneList;
    int numCurrent;
    bool stoneTmp[19][19];
    QPoint *koPoint;

    void initStoneTmp();
    int getStonesLiberty(int x, int y);
    void clearDead(int x, int y);
    int removeStones(int x, int y);
    bool canCapture(int x, int y);
};

#endif

