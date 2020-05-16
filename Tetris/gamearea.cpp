#include "gamearea.h"
#include "blockmatrix.h"

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QCoreApplication>
#include <QPen>
#include <QDebug>
#include <vector>
#include <QKeyEvent>
#include <QRandomGenerator>

GameArea::GameArea(QObject* parent):
    QGraphicsScene(parent)
{
    setSceneRect(10,10, 220,460);
    blockMatrixPtr_ = new blockMatrix();
    connect(blockMatrixPtr_, &blockMatrix::removeSquare, this, &GameArea::removeSquare);
}

void GameArea::addTetromino()
{
    int randomNumber = QRandomGenerator::global()->bounded(16384)%2;
    activeTetromino_ = new Tetromino();
    connect(activeTetromino_, &Tetromino::addSquare, this, &GameArea::addSquare);
    connect(activeTetromino_, &Tetromino::blockStopped, this, &GameArea::addTetromino);
    activeTetromino_->setType(randomNumber);
}

bool GameArea::isOutOfBounds(int x)
{
    return ( x < 0 or x > 220 );
}

void GameArea::tetrominoFall()
{
    bool isBroken = false;
    QPoint pos;
    for ( auto square : activeTetromino_->squares ) {
        pos = getPos(square);
        if ( square->y() + 20 > 460 ) {
            isBroken = true;
            break;
        }
        else {
            if ( !blockMatrixPtr_->isSpaceAvailable( {pos.x(), pos.y() + 1} ) ) {
                isBroken = true;
                break;
            }
        }
    }
    if ( isBroken ) {
        blockMatrixPtr_->addSquares(activeTetromino_->squares);
        blockMatrixPtr_->checkRows();
        addTetromino();
    }
    else {
        activeTetromino_->moveDown();
    }
}

void GameArea::tetrominoTryLeft()
{
    bool canMove = true;
    QPoint pos;
    for ( auto square : activeTetromino_->squares ) {
        pos = getPos(square);
        if ( isOutOfBounds(square->x() - 20) ) {
            canMove = false;
        }
        else if ( !blockMatrixPtr_->isSpaceAvailable( {pos.x() - 1, pos.y()} ) ) {
            canMove = false;
        }
    }
    if ( canMove ) {
        activeTetromino_->moveLeft();
    }
}

void GameArea::tetrominoTryRight()
{
    bool canMove = true;
    QPoint pos;
    for ( auto square : activeTetromino_->squares ) {
        pos = getPos(square);
        if ( isOutOfBounds(square->x() + 20) ) {
            canMove = false;
        }
        else if ( !blockMatrixPtr_->isSpaceAvailable( {pos.x() + 1, pos.y()} ) ) {
            canMove = false;
        }
    }
    if ( canMove ) {
        activeTetromino_->moveRight();
    }
}

void GameArea::tetrominoTryTurn()
{
    qDebug() << "pyöritettään";
    activeTetromino_->tetrominoTurn();
}

QPoint GameArea::getPos(QGraphicsRectItem* item)
{
    int xPos = ( (int)item->x() ) / 20;
    int yPos = ( (int)item->y() ) / 20;
    return {xPos, yPos};
}

void GameArea::keyPressEvent(QKeyEvent * event)
{
    switch ( event->key() ) {
    case Qt::Key_Left:
        tetrominoTryLeft();
        break;
    case Qt::Key_Right:
        tetrominoTryRight();
        break;
    case Qt::Key_Z:
        tetrominoTryTurn();
        break;
    }
}

void GameArea::removeSquare(QGraphicsRectItem *square)
{
    removeItem(square);
}

void GameArea::addSquare(QGraphicsRectItem *square, QPointF coord, QBrush color)
{
    square->setPen(black);
    square->setBrush(color);
    addItem(square);
    square->setPos(coord);
}
