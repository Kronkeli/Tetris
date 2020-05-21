#include "mainwindow.h"
#include "gamearea.h"
#include "nextblock.h"

#include <QApplication>
#include <QObject>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    NextBlock nextblock;
    GameArea gamearea(nextblock);
    MainWindow w(gamearea, nextblock);

    w.show();
    return a.exec();
}
