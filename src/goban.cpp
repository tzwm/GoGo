#include "goban.h"

Goban::Goban()
{
    gobanView = new GobanView();
    gobanView->setGoban(this);
    gobanView->show();
    
    for(int i=0;i<19;i++)
       for(int j=0;j<19;j++)
          stoneOnGoban[i][j] = NULL; 

    numCurrent = 0;
}


void Goban::addStone(QPoint& pos, StoneItem* stone)
{
    numCurrent++;
    stoneOnGoban[pos.x()][pos.y()] = stone;
}

bool Goban::canPlay(QPoint& pos)
{
    if(stoneOnGoban[pos.x()][pos.y()])
        return false;

    return true;
}

int Goban::getNumCurrent()
{
    return numCurrent;
}

