#include "mainwindow.h"
#include "gamearea.h"

#include <QApplication>
#include <QObject>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    GameArea gamearea;
    MainWindow w(gamearea);

    w.show();
    return a.exec();
}
