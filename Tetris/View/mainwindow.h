#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Model/gamearea.h"
#include "View/nextblock.h"

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
    void showOptionsDialog();
    void setDifficulty(int interval);
    void endGame();
    void gameOver(bool playAgain);

signals:

    void gameStarted();
    void togglePause(bool isPaused);

private:

    QGraphicsView view_;
    QGraphicsView nextBlockView_;

    GameArea* scene_;
    NextBlock* nextBlockScene_;

    QTimer* timer_;

    bool isPaused_ = true;

    int interval_ = 300;
};
#endif // MAINWINDOW_H
