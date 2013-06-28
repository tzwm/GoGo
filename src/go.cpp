#include "go.h"

Go::Go()
{
    goban = NULL;
    gobanView = NULL;
    controller = NULL;

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
