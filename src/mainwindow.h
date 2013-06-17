#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "goban.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;
    Goban* goban;

    void init();
};

#endif // MAINWINDOW_H
