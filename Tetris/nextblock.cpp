#include "nextblock.h"

#include <QDebug>

NextBlock::NextBlock(QObject* parent):
    QGraphicsScene(parent)
{
    setSceneRect(10,10, 60, 60);
}

void NextBlock::updateNextBlock(int nexttetromino)
{
    clear();
    Tetromino* nextTetromino = new Tetromino( { 20, 20 } );
    connect(nextTetromino, &Tetromino::addSquareToScene, this, &NextBlock::addSquareToScene);
    nextTetromino->setType(nexttetromino);
    delete nextTetromino;
}

void NextBlock::addSquareToScene(QGraphicsRectItem *square, QPointF coord, QBrush color)
{
    square->setPen(black);
    square->setBrush(color);
    addItem(square);
    square->setPos(coord);
}
