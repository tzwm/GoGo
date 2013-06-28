#include "sidebar.h"

Sidebar::Sidebar()
{
    ppBtn = new QPushButton("双人对战", this);
    pcBtn = new QPushButton("人机对战", this);
    undoBtn = new QPushButton("悔棋", this);
    scoreBtn = new QPushButton("数子", this);
    exitBtn = new QPushButton("退出", this);

    init();
}

void Sidebar::init()
{   
    setWindowOpacity(1);
    setFixedSize(110, 290);
    move(QPoint(1000, 200));

    ppBtn->show();
    pcBtn->show();
    undoBtn->show();
    scoreBtn->show();
    exitBtn->show();

    ppBtn->setFixedSize(90, 40);
    ppBtn->move(10 , 10);

    pcBtn->setFixedSize(90, 40);
    pcBtn->move(10 , 60);

    undoBtn->setFixedSize(90, 40);
    undoBtn->move(10 , 110);

    scoreBtn->setFixedSize(90, 40);
    scoreBtn->move(10 , 160);
    
    exitBtn->setFixedSize(90, 40);
    exitBtn->move(10 , 210);
    
    connect(ppBtn, SIGNAL(released()), this, SLOT(pressPPBtn()));
    connect(pcBtn, SIGNAL(released()), this, SLOT(pressPCBtn()));
    connect(undoBtn, SIGNAL(released()), this, SLOT(pressUndoBtn()));
    connect(scoreBtn, SIGNAL(released()), this, SLOT(pressScoreBtn()));
    connect(exitBtn, SIGNAL(released()), this, SLOT(pressExitBtn()));
}

void Sidebar::setGo(Go* _go)
{
    go = _go;
}

void Sidebar::pressPPBtn()
{
    go->close();
    go->newGame(0); 
}

void Sidebar::pressPCBtn()
{
    go->close();
    go->newGame(1);
}

void Sidebar::pressUndoBtn()
{
    if(go->getGoban() == NULL)
        return;
    go->getGoban()->undo();
    go->getGobanView()->redraw();
}

void Sidebar::pressScoreBtn()
{
    bool ret = go->checkScore();

    if(!ret)
    {
        go->getGobanView()->setWindowTitle("游戏还没有结束");
        return;
    }

    if(go->getScoreBlack() >= 185)
        go->getGobanView()->setWindowTitle("黑色胜利");
    else
        go->getGobanView()->setWindowTitle("白色胜利");

}

void Sidebar::pressExitBtn()
{
    exit(0);
}
