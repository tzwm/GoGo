#ifndef __GO_H__
#define __GO_H__

#include "controllerGTP.h"
#include "goban.h"
#include "gobanView.h"
#include "helper.h"

class Go
{
public:
    Go();
    ~Go();
    void showGobanView();
    void showSidebar();

private:
    Goban *goban;
    GobanView *gobanView;
    Controller_GTP *controller;


};

#endif

