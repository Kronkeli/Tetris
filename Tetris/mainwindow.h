#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "gamearea.h"
#include "nextblock.h"

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QKeyEvent>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(GameArea &scene_, NextBlock &nextblockscene, QWidget *parent = nullptr);

public slots:

    void startGame();
    void pauseGame();

signals:

    void gameStarted();
    void togglePause(bool isPaused);

private:
    QGraphicsView view_;
    QGraphicsView nextBlockView_;

    GameArea* scene_;
    NextBlock* nextBlockScene_;

    QTimer* timer_;

    bool isPaused_ = false;

    int interval_ = 100;
};
#endif // MAINWINDOW_H
