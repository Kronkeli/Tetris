#ifndef GAMEAREA_H
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
    bool isXOutOfBounds(int x);
    bool isYOutOfBounds(int y);
    void tetrominoFall();
    bool tetrominoTryLeft(int amount = 1);
    bool tetrominoTryRight(int amount = 1);
    void tetrominoTryTurn();
    void togglePauseSituation(bool isPaused);
    QPoint getPos(QGraphicsRectItem* item);
    void keyPressEvent(QKeyEvent* event);
    void removeSquare(QGraphicsRectItem* square);
    void addSquareToScene(QGraphicsRectItem* square, QPointF coord, QBrush color);
    bool isGameOver(Tetromino* tetromino);
    void restartScene();
    void setDifficulty( int level);

private:

    Tetromino* activeTetromino_;
    NextBlock* nextBlockScene_;
    int nextTetromino_;
    blockMatrix* blockMatrixPtr_;
    bool keyPressIgnore_ = true;
    int difficulty_ = 2;
    int score_;
    void addScore(int rowsDeleted);

signals:
    void tetrominoChanged(int nextTetromino);
    void pauseGame();
    void gameOver();
    void displayScore(int score);
};

#endif // GAMEAREA_H
