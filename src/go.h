#ifndef __GO_H__
#define __GO_H__

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

    int mode;

private:
    Goban *goban;
    GobanView *gobanView;
    Controller_GTP *controller;
    Sidebar *sidebar;
};

#endif

