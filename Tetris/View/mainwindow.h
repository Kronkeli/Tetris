#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Model/gamearea.h"
#include "View/nextblock.h"

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QLabel>

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
    void showScore(int scoreAmount);

signals:

    void gameStarted();
    void togglePause(bool isPaused);
    void changeDifficulty(int level);

private:

    QGraphicsView view_;
    QGraphicsView nextBlockView_;

    GameArea* scene_;
    NextBlock* nextBlockScene_;

    QTimer* timer_;

    bool isPaused_ = true;
    bool isRunning_ = false;

    int interval_ = 500;

    QLabel* scoreLabel_;
};
#endif // MAINWINDOW_H
