#ifndef GAMEAREA_H
#define GAMEAREA_H

#include "tetromino.h"
#include "blockmatrix.h"

#include <QGraphicsScene>
#include <map>
#include <QVirtualKeyboardInputEngine>

class GameArea: public QGraphicsScene
{
    Q_OBJECT
public:
    GameArea(QObject* parent = nullptr);

    void newTetromino();

public slots:

    void addTetromino();

    bool isOutOfBounds(int x);

    void tetrominoFall();

    void tetrominoTryLeft();

    void tetrominoTryRight();

    void tetrominoTryTurn();

    QPoint getPos(QGraphicsRectItem* item);

    void keyPressEvent(QKeyEvent * event);

    void removeSquare(QGraphicsRectItem* square);

    void addSquare(QGraphicsRectItem* square, QPointF coord, QBrush color);

private:

    Tetromino *activeTetromino_;

    blockMatrix *blockMatrixPtr_;

};

#endif // GAMEAREA_H
