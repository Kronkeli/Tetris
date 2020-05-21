#ifndef GAMEAREA_H
#define GAMEAREA_H

#include "tetromino.h"
#include "blockmatrix.h"
#include "nextblock.h"

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

    void keyPressEvent(QKeyEvent * event);

    void removeSquare(QGraphicsRectItem* square);

    void addSquareToScene(QGraphicsRectItem* square, QPointF coord, QBrush color);

private:

    Tetromino* activeTetromino_;

    NextBlock* nextBlockScene_;

    int nextTetromino_;

    blockMatrix* blockMatrixPtr_;

    bool keyPressIgnore_ = false;

signals:
    void tetrominoChanged(int nextTetromino);
};

#endif // GAMEAREA_H
