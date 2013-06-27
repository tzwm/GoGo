#include <QApplication>

#include "go.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Go *go = new Go();
    go->showGobanView();

    return a.exec();
}
