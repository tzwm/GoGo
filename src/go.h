#ifndef __GO_H__
#define __GO_H__

#include <string>

#include "controllerGTP.h"
#include "goban.h"
#include "gobanView.h"
#include "helper.h"
#include "sidebar.h"

class Sidebar;
class GobanView;
class Goban;

class Go
{
public:
    Go();
    ~Go();
    void showGobanView();
    void showSidebar();
    void newGame(int _mode);
    void close();
    Goban* getGoban();
    GobanView* getGobanView();
    bool checkScore();
    int getScoreBlack();
    int getScoreWhite();    

    int mode;

private:
    Goban *goban;
    GobanView *gobanView;
    Controller_GTP *controller;
    Sidebar *sidebar;

    int scoreBlack;
    int scoreWhite;
    int colorTmp;
    bool stonesTmp[19][19];

    int checkPoint(int x, int y);
};

#endif

