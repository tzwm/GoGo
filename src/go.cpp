#include "go.h"

Go::Go()
{
    goban = NULL;
    gobanView = NULL;
    controller = NULL;

    scoreBlack = 0;
    scoreWhite = 0;
    colorTmp = -1;
    memset(stonesTmp, 0, sizeof(stonesTmp));

    sidebar = new Sidebar(); 
    sidebar->setGo(this);
}

void Go::newGame(int _mode)
{    
    goban = new Goban();
    gobanView = new GobanView();
    controller = new Controller_GTP();

    gobanView->setGoban(goban);
    gobanView->setGo(this);
    goban->setController(controller);
    goban->setGo(this);

    showGobanView();

    mode = _mode;
}

void Go::showGobanView()
{
    gobanView->show();
}

void Go::showSidebar()
{
    sidebar->show();
}

void Go::close()
{
    if(gobanView)
        gobanView->close();
    if(controller)
        controller->quitEngine();     
}

Goban* Go::getGoban()
{
    return this->goban;
}

GobanView* Go::getGobanView()
{
    return this->gobanView;
}

bool Go::checkScore()
{
    scoreBlack = 0;
    scoreWhite = 0;
    colorTmp = -1;
    memset(stonesTmp, 0, sizeof(stonesTmp));

    for(int i = 0; i<19;i++)
        for(int j=0;j<19;j++)
        {
            if(stonesTmp[i][j])
                continue;

            stonesTmp[i][j] = true;
            if(goban->stone10[i][j] == 0)
                scoreBlack++;
            if(goban->stone10[i][j] == 1)
                scoreWhite++;
            if(goban->stone10[i][j] != -1)
                continue;

            colorTmp = -1;
            int tot = checkPoint(i, j);
            if(tot == -1)
            {
                scoreBlack = -1;
                scoreWhite = -1;
                return false;
            }
            if(colorTmp == 0)
                scoreBlack += tot;
            if(colorTmp == 1)
                scoreWhite += tot;
        }

    return true;
}

int Go::checkPoint(int x, int y)
{
    stonesTmp[x][y] = true;

    int tot = 1;
    for(int i=0;i<4;i++)
    {
        int xx = x + Helper::d[0][i];
        int yy = y + Helper::d[1][i];
        if(xx<0||xx>18||yy<0||yy>18)
            continue;

        if(goban->stone10[xx][yy] != -1)
        {
            if(colorTmp == -1)
            {
                colorTmp = goban->stone10[xx][yy];
                continue;
            }
            if(goban->stone10[xx][yy] != colorTmp)
                return -1;
        }
        else
        {
            if(stonesTmp[xx][yy])
                continue;
            int tmp = checkPoint(xx, yy);
            if(tmp == -1)
                return -1;
            tot += tmp;
        }
    }

    return tot;
}

int Go::getScoreBlack()
{
    return scoreBlack;
}

int Go::getScoreWhite()
{
    return scoreWhite;
}

