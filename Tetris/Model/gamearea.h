﻿#ifndef GAMEAREA_H
#define GAMEAREA_H

#include "Model/tetromino.h"
#include "Model/blockmatrix.h"
#include "View/nextblock.h"

#include <QGraphicsScene>
#include <map>
#include <QVirtualKeyboardInputEngine>

class GameArea: public QGraphicsScene
{
    Q_OBJECT
public:
    GameArea(NextBlock &nextblockscene, QObject* parent = nullptr);

    void newTetromino();

public slots:

    void addTetromino();
    bool isOutOfBounds(int x);
    void tetrominoFall();
    void tetrominoTryLeft();
    void tetrominoTryRight();
    void tetrominoTryTurn();
    void togglePauseSituation(bool isPaused);
    QPoint getPos(QGraphicsRectItem* item);
    void keyPressEvent(QKeyEvent* event);
    void removeSquare(QGraphicsRectItem* square);
    void addSquareToScene(QGraphicsRectItem* square, QPointF coord, QBrush color);
    bool isGameOver(Tetromino* tetromino);
    void restartScene();

private:

    Tetromino* activeTetromino_;
    NextBlock* nextBlockScene_;
    int nextTetromino_;
    blockMatrix* blockMatrixPtr_;
    bool keyPressIgnore_ = true;

signals:
    void tetrominoChanged(int nextTetromino);
    void gameOver();
};

#endif // GAMEAREA_H