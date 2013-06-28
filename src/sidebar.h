#ifndef __SIDEBAR_H__
#define __SIDEBAR_H__

#include <QDialog>
#include <QPoint>
#include <QPushButton>

#include "go.h"

class Go;
class GobanView;
class Goban;

class Sidebar : public QDialog 
{
    Q_OBJECT

public:
    Sidebar();
    void init();
    void setGo(Go *_go);

private:
    Go *go;
    QPushButton *ppBtn;
    QPushButton *pcBtn;
    QPushButton *undoBtn;
    QPushButton *scoreBtn;
    QPushButton *exitBtn;

private slots:
    void pressPPBtn();
    void pressPCBtn();
    void pressUndoBtn();
    void pressScoreBtn();
    void pressExitBtn();
};


#endif

