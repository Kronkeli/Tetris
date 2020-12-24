#include "View/mainwindow.h"
#include "Model/gamearea.h"
#include "View/nextblock.h"

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
