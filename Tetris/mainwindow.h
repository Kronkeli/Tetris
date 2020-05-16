#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "gamearea.h"

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QKeyEvent>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(GameArea &scene_, QWidget *parent = nullptr);

public slots:

    void startGame();
    void pauseGame();

signals:

    void gameStarted();

private:
    QGraphicsView view_;

    GameArea* scene_;

    QTimer* timer_;

    bool isPaused_ = false;

    int interval_ = 100;
};
#endif // MAINWINDOW_H
