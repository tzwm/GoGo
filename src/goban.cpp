#include "goban.h"

Goban::Goban()
{
    for(int i=0;i<19;i++)
       for(int j=0;j<19;j++)
       {
            stoneOnGoban[i][j] = NULL; 
            stone10[i][j] = -1;
       }

    numCurrent = 0;
    koPoint = NULL;
}

void Goban::setController(Controller_GTP *_con)
{
    this->controller = _con;
}

void Goban::setGo(Go *_go)
{
    this->go = _go;
}

void Goban::play(QPoint& pos, StoneItem* stone)
{
    addStone(pos, stone);

    if(go->mode == 1)
        bool ret = controller->play(Controller_GTP::b, Helper::pointToGo(pos));
}

void Goban::addStone(QPoint& pos, StoneItem* stone)
{
    numCurrent++;
    stoneOnGoban[pos.x()][pos.y()] = stone;
    stone10[pos.x()][pos.y()] = (numCurrent -1) %2;
    stoneList.push_back(stone);

    koPoint = NULL;
    clearDead(pos.x(), pos.y()); 
}

bool Goban::canPlay(QPoint& pos)
{
    if(stoneOnGoban[pos.x()][pos.y()])
        return false;

    bool ret = true;
    initStoneTmp();
    stone10[pos.x()][pos.y()] = numCurrent %2;
    int liberty = getStonesLiberty(pos.x(), pos.y());
    if(liberty == 0)
    {
        if(!canCapture(pos.x(), pos.y()))
            ret = false;
        if(koPoint && pos == *koPoint)
            ret = false;
    }   

    stone10[pos.x()][pos.y()] = -1;
    return ret;
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
    stoneTmp[x][y] = true;

    int tot = 0;
    for(int i=0;i<4;i++)
    {
        int xx = x +Helper::d[0][i];
        int yy = y +Helper::d[1][i];
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

void Goban::clearDead(int x, int y)
{
    bool getTmp = false;

    for(int i=0;i<4;i++)
    {
        int xx = x +Helper::d[0][i];
        int yy = y +Helper::d[1][i];

        if(xx<0||xx>18||yy<0||yy>18)
            continue;
        if(stone10[xx][yy] != numCurrent %2)
            continue;
        
        initStoneTmp();
        int liberty = getStonesLiberty(xx, yy);
        if(liberty == 0)
        {
            if(removeStones(xx, yy) == 1)
            {
                if(getTmp)
                {
                    koPoint = NULL;
                    continue;
                }
                getTmp = true;
                koPoint = new QPoint(xx, yy);
            }
        }
    }
}

int Goban::removeStones(int x, int y)
{
    int color = stone10[x][y]; 
    stoneOnGoban[x][y]->setDead();
    stoneOnGoban[x][y] = NULL;
    stone10[x][y] = -1;
   
    int tot = 1;  
    for(int i=0;i<4;i++)
    {
        int xx = x +Helper::d[0][i];
        int yy = y +Helper::d[1][i];
        if(xx<0||xx>18||yy<0||yy>18)
            continue;
        if(stone10[xx][yy] == color)
           tot += removeStones(xx, yy); 
    }

    return tot;
}

StoneItem* Goban::getStone(int num)
{
    return stoneList[num];
}

bool Goban::canCapture(int x, int y)
{
    int color = numCurrent %2;
    for(int i=0;i<4;i++)
    {
        int xx = x +Helper::d[0][i];
        int yy = y +Helper::d[1][i];
        if(xx<0||xx>18||yy<0||yy>18)
            continue;
        if(stone10[xx][yy] != (color ^ 1))
            continue;

        initStoneTmp();
        int liberty = getStonesLiberty(xx, yy);
        if(liberty == 0)
            return true;
    }

    return false;
}

bool Goban::genPlay()
{
    QPoint move = Helper::goToPoint(controller->genmove(Controller_GTP::w));
    StoneItem *stone = new StoneItem(numCurrent % 2,  move, numCurrent +1);
    stone->setPos(Helper::toCoord(move, gobanView->sizeGrid));
    addStone(move, stone);
}

void Goban::undo()
{
    numCurrent--;
    StoneItem* stone = *(stoneList.end() -1);
    QPoint pos = stone->getStonePos();
    stoneList.pop_back();
    stoneOnGoban[pos.x()][pos.y()] = NULL;
    stone10[pos.x()][pos.y()] = -1;

    if(go->mode == 1)
        controller->undo();
}
