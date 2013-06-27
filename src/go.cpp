#include "go.h"

Go::Go()
{
    goban = new Goban();
    gobanView = new GobanView();
    controller = new Controller_GTP();

    gobanView->setGoban(goban);
    goban->setController(controller);

}

void Go::showGobanView()
{
    gobanView->show();
}

void Go::showSidebar()
{

}
