#ifndef __GOBAN_H__
#define __GOBAN_H__

#include <vector>
#include <QPoint>

#include "helper.h"
#include "gobanView.h"
#include "stoneItem.h"

class GobanView;

class Goban 
{
public:
    Goban();
    void addStone(QPoint& pos, StoneItem* stone);
    bool canPlay(QPoint& pos);
    int getNumCurrent();

private:
    GobanView* gobanView;
    StoneItem* stoneOnGoban[19][19];
    std::vector<StoneItem*> stoneList;
    int numCurrent;
};

#endif

