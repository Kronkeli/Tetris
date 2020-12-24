#include "Model/gamearea.h"
#include "Model/blockmatrix.h"

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QCoreApplication>
#include <QPen>
#include <QDebug>
#include <vector>
#include <QKeyEvent>
#include <QRandomGenerator>

GameArea::GameArea(NextBlock &nextblockscene, QObject* parent):
    QGraphicsScene(parent)
{
    nextBlockScene_ = &nextblockscene;
    setSceneRect(10,10, 220,460);

    blockMatrixPtr_ = new blockMatrix();
    connect(blockMatrixPtr_, &blockMatrix::removeSquare, this, &GameArea::removeSquare);
    connect(this, &GameArea::tetrominoChanged, nextBlockScene_, &NextBlock::updateNextBlock);

    nextTetromino_ = QRandomGenerator::global()->bounded(16384)%7;

    QPen black(Qt::black);
    QBrush yellow(Qt::yellow);
    QBrush red(Qt::red);
    QBrush blue(Qt::blue);
    QBrush darkblue(Qt::darkBlue);
    QGraphicsRectItem* s1 = addRect(0,0,20,20,black, darkblue);
    s1->setPos(220,0);
    QGraphicsRectItem* s2 = addRect(0,0,20,20,black, yellow);
    s2->setPos(230,20);
//    QGraphicsRectItem* s3 = addRect(0,0,20,20,black, red);
//    s3->setPos(120,0);
//    QGraphicsRectItem* s4 = addRect(0,0,20,20,black, blue);
//    s4->setPos(140,0);
}

void GameArea::addTetromino()
{
    keyPressIgnore_ = false;
    activeTetromino_ = new Tetromino({100, 0});
    connect(activeTetromino_, &Tetromino::addSquareToScene, this, &GameArea::addSquareToScene);
    connect(activeTetromino_, &Tetromino::blockStopped, this, &GameArea::addTetromino);
    activeTetromino_->setType(nextTetromino_);
    if ( isGameOver( activeTetromino_ ) == true ) {
        qDebug() << "is over";
        emit gameOver();
    }
    nextTetromino_ = QRandomGenerator::global()->bounded(16384)%7;
    emit tetrominoChanged(nextTetromino_);
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
    activeTetromino_->tetrominoTurn();
    QPoint pos;
    bool inArea = false;
        for ( QGraphicsRectItem* square : activeTetromino_->squares ) {
            pos = getPos( square );
            qDebug() << "sijainti: " << pos.x();
            inArea = true;
            if ( pos.x() < 0 ) {
                qDebug() << "vasemmalla";
                inArea = false;
                activeTetromino_->moveRight();
            }
           else if ( pos.x() > 11 ) {
                qDebug() << "oikealla";
                inArea = false;
                activeTetromino_->moveLeft();
            }
        }
}

void GameArea::togglePauseSituation(bool isPaused)
{
    keyPressIgnore_ = isPaused;
}

QPoint GameArea::getPos(QGraphicsRectItem* item)
{
    int xPos = ( (int)item->x() ) / 20;
    int yPos = ( (int)item->y() ) / 20;
    return {xPos, yPos};
}

void GameArea::keyPressEvent(QKeyEvent * event)
{
    if ( keyPressIgnore_ ) {
        event->ignore();
    }
    else {
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
        case Qt::Key_Down:
            tetrominoFall();
            break;
        }
    }
}

void GameArea::removeSquare(QGraphicsRectItem *square)
{
    removeItem(square);
}

void GameArea::addSquareToScene(QGraphicsRectItem *square, QPointF coord, QBrush color)
{
    square->setPen(black);
    square->setBrush(color);
    addItem(square);
    square->setPos(coord);
}

bool GameArea::isGameOver(Tetromino* tetromino)
{
    QPoint point;
    bool canBeAdded = true;
    for (QGraphicsRectItem* square : tetromino->squares ) {
        point = getPos(square);
        if ( !blockMatrixPtr_->isSpaceAvailable( point ) ) {
            canBeAdded = false;
        }
    }
    return !canBeAdded;
}

void GameArea::restartScene()
{
    blockMatrixPtr_->clearData();
}
