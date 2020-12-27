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

bool GameArea::isXOutOfBounds(int x)
{
    return ( x < 0 or x > 220 );
}

bool GameArea::isYOutOfBounds(int y)
{
    return( y < 0 or y > 479 );
}

void GameArea::tetrominoFall()
{
    // isBroken parameter tells if moving is possible
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
        int rowsDeleted = blockMatrixPtr_->checkRows();
        addScore( rowsDeleted );
        emit displayScore(score_);
        addTetromino();
    }
    else {
        activeTetromino_->moveDown();
    }
}

bool GameArea::tetrominoTryLeft(int amount)
{
    bool canMove = true;
    QPoint pos;
    for ( auto square : activeTetromino_->squares ) {
        pos = getPos(square);
        if ( isXOutOfBounds(square->x() - amount * 20) ) {
            canMove = false;
        }
        else if ( !blockMatrixPtr_->isSpaceAvailable( {pos.x() - amount, pos.y()} ) ) {
            canMove = false;
        }
    }
    return canMove;
}

bool GameArea::tetrominoTryRight(int amount)
{
    bool canMove = true;
    QPoint pos;
    qDebug() << "tryMoveRight ";
    for ( auto square : activeTetromino_->squares ) {
        pos = getPos(square);
        qDebug() << "trytomoveright yksi square: { x : " << pos.x() << ", y : "  << pos.y() << " }";
        if ( isXOutOfBounds(square->x() + amount * 20) ) {
            canMove = false;
        }
        else if ( !blockMatrixPtr_->isSpaceAvailable( {pos.x() + amount, pos.y()} ) ) {
            canMove = false;
        }
    }
    return canMove;
}

void GameArea::tetrominoTryTurn()
{
    /* Palikan kääntöalgoritmi:
     - Käännä palikkaa
     - Jos onnistui HYVÄ
     - Jos ei onnistu (ulkona alueesta tai palikan sisällä), kokeile kunnes onnistuu:
       - Siirto oik 1
       - Siirto oik 2
       - Siirto vas 1
       - Siirto vas 2
       - PERUUTA KÄÄNTÖ
*/
    // KOkeillaan:
    activeTetromino_->tetrominoTurn();
    QPoint pos;
    bool canTurnFreely = true;
    bool YOutOfBounds = false;

int helpCounter = 1;
    for ( QGraphicsRectItem* square : activeTetromino_->squares ) {
        qDebug() << "Kierretään palikoita " << helpCounter << "/4";

        pos = getPos( square );
        qDebug() << "sijainti : { x : " << pos.x() << ", y : " << pos.y() << " }";
        // Check if block is out of bounds (either x or y)
        qDebug()<< "Testataan out of bounds blokille " << helpCounter << "/4";
        if ( isXOutOfBounds( pos.x() * 20) ) {
            qDebug() << "x on pilalla";
            canTurnFreely = false;
        }
        else if ( isYOutOfBounds( pos.y() * 20) ) {
            qDebug() << "Y on pilalla";
            YOutOfBounds = true;
        }
        // Check if blocked by blocks
        else if (not blockMatrixPtr_->isSpaceAvailable( pos ) ) {
            canTurnFreely = false;
        }
        helpCounter++;
    }

    // Try wall kick
    if ( YOutOfBounds ) {
        qDebug() << "Y is out of bounds -> ABORT ";
        activeTetromino_->tetrominoTurn( -1 );
    }
    else if (not canTurnFreely) {
        qDebug() << "Trying wall kickeros";
        if ( tetrominoTryRight() ) {
            activeTetromino_->moveRight();
        }
        else if ( tetrominoTryRight(2) ) {
            activeTetromino_->moveRight(2);
        }
        else if ( tetrominoTryLeft() ) {
            activeTetromino_->moveLeft();
        }
        else if ( tetrominoTryLeft(2) ) {
            activeTetromino_->moveLeft(2);
        }
        // No action can make turning possible -> UNDO TURN
        else {
            qDebug() << "Wall kickeros EI TOIMI";
            activeTetromino_->tetrominoTurn( -1 );
        }
    }
    qDebug() << "TRYTOTURN PÄÄSI LOPPUUN";
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
    if ( event->key() == Qt::Key_Space ) {
        emit pauseGame();
    }
    else if ( keyPressIgnore_ ) {
        event->ignore();
    }
    else {
        switch ( event->key() ) {
        case Qt::Key_Left:
            if ( tetrominoTryLeft() ) {
                activeTetromino_->moveLeft();
            }
            break;
        case Qt::Key_Right:
            if ( tetrominoTryRight() ) {
                activeTetromino_->moveRight();
            }
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
    score_ = 0;
    emit displayScore(score_);
}

void GameArea::setDifficulty(int level)
{
    difficulty_ = level;
}

void GameArea::addScore(int rowsDeleted)
{
    // Score is calculated by the amount of line amount (more points from more lines)
    // multiplied by diffilty level.
    int scoreFromLines = 0;
    switch( rowsDeleted ) {
    case 1:
        scoreFromLines = 40;
        break;
    case 2:
        scoreFromLines = 100;
        break;
    case 3:
        scoreFromLines = 300;
        break;
    case 4:
        scoreFromLines = 1200;
        break;
    }
    int scoreToAdd = difficulty_ * scoreFromLines;
    score_ = score_ + scoreToAdd;
}
