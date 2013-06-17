#include "goban.h"

Goban::Goban()
{
    gobanView = new GobanView();
    gobanView->setGoban(this);
    gobanView->show();
    
    for(int i=0;i<19;i++)
       for(int j=0;j<19;j++)
       {
            stoneOnGoban[i][j] = NULL; 
            stone10[i][j] = -1;
       }

    numCurrent = 0;
}


void Goban::addStone(QPoint& pos, StoneItem* stone)
{
    numCurrent++;
    stoneOnGoban[pos.x()][pos.y()] = stone;
    stone10[pos.x()][pos.y()] = (numCurrent -1) %2;
    stoneList.push_back(stone);

    clearDead(); 
}

bool Goban::canPlay(QPoint& pos)
{
    if(stoneOnGoban[pos.x()][pos.y()])
        return false;

    initStoneTmp();
    stone10[pos.x()][pos.y()] = numCurrent %2;
    int liberty = getStonesLiberty(pos.x(), pos.y());
    stone10[pos.x()][pos.y()] = -1;
    if(liberty == 0)
        return false;

    return true;
}

int Goban::getNumCurrent()
{
    return numCurrent;
}

StoneItem* Goban::getStoneOnGoban(int x, int y)
{
    return stoneOnGoban[x][y];
}

int Goban::getStonesLiberty(int x, int y)
{
    int d[2][4] = {{-1, 1, 0, 0}, {0, 0, -1, 1}};
   
    stoneTmp[x][y] = true;

    int tot = 0;
    for(int i=0;i<4;i++)
    {
        int xx = x +d[0][i];
        int yy = y +d[1][i];
        if(xx<0||xx>18||yy<0||yy>18)
            continue;
        if(stoneTmp[xx][yy])
            continue;
        if(stone10[xx][yy] == -1)
            tot++;
        if(stone10[xx][yy] == stone10[x][y])
            tot += getStonesLiberty(xx, yy); 
    }
    
    return tot;
}

void Goban::initStoneTmp()
{
    for(int i=0;i<19;i++)
        for(int j=0;j<19;j++)
            stoneTmp[i][j] = false;
}

void Goban::clearDead()
{
    initStoneTmp();
    
    for(int i=0;i<19;i++)
       for(int j=0;j<19;j++)
       {
           if(stone10[i][j] != 0 && stone10[i][j] != 1)
               continue;
           if(stoneTmp[i][j])
               continue;

           int liberty = getStonesLiberty(i, j);
           if(liberty == 0)
               removeStones(i, j);
       } 
}

void Goban::removeStones(int x, int y)
{
    int d[2][4] = {{-1, 1, 0, 0}, {0, 0, -1, 1}};
   
    int color = stone10[x][y]; 
    stoneOnGoban[x][y]->setDead();
    stoneOnGoban[x][y] = NULL;
    stone10[x][y] = -1;
     
    for(int i=0;i<4;i++)
    {
        int xx = x +d[0][i];
        int yy = y +d[1][i];
        if(xx<0||xx>18||yy<0||yy>18)
            continue;
        if(stone10[xx][yy] == color)
           removeStones(xx, yy); 
    }
}

StoneItem* Goban::getStone(int num)
{
    return stoneList[num];
}
