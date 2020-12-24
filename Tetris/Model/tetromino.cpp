#include "Model/tetromino.h"

#include <QGraphicsScene>
#include <QRandomGenerator>
#include <QDebug>
#include <set>
#include <QMainWindow>
#include <iostream>

Tetromino::Tetromino(QPointF coordinate)
{
    pointOfCreation_ = coordinate;
}

void Tetromino::moveDown()
{
    for ( auto square : squares ) {
        square->moveBy(0,20);
    }
    weightPoint_.setY( weightPoint_.y() + 20 );
}

void Tetromino::moveLeft()
{
    for ( auto square : squares ) {
        square->moveBy(-20, 0);
    }
    weightPoint_.setX( weightPoint_.x() - 20 );
}

void Tetromino::moveRight()
{
    for ( auto square : squares ) {
        square->moveBy(20, 0);
    }
    weightPoint_.setX( weightPoint_.x() + 20 );
}

void Tetromino::tetrominoTurn()
{
    float dx;
    float dy;
    for ( QGraphicsRectItem* square : squares ) {
        dx = weightPoint_.x() - square->x();
        dy = weightPoint_.y() - square->y();
            square->setX( weightPoint_.x() + dy );
            square->setY( weightPoint_.y() - dx );
    }
}

void Tetromino::setType(int number)
{
    std::string type = TETROMINOS[number];
    qreal x = pointOfCreation_.x();
    qreal y = pointOfCreation_.y();

    for ( int i = 0; i < 4; i++ ) {
        squares.push_back( new QGraphicsRectItem(0, 0, SIZE, SIZE) );
    }
    if ( type == "I" ) {
        for ( int i = 0; i < 4; i++ ) {
            emit addSquareToScene(squares[i], { x - 20 + i*20, y}, blue);
        }
        weightPoint_ = {x + 10, y + 10};
    }
    else if ( type == "O" ) {
        int index = 0;
        for ( int i = 0; i < 2; i++ ) {
            for ( int j = 0; j < 2; j++ ) {
                emit addSquareToScene(squares[index], {x + i*20, y + j*20}, yellow);
                index++;
            }
        }
        weightPoint_ = { x + 10, y +10 };
    }
    else if ( type == "T" ) {
        for ( auto i = 0; i < 3; i++ ) {
            emit addSquareToScene(squares[i], {x + i*20, y + 20}, purple);
        }
        emit addSquareToScene( squares[3], {x + 20, y}, purple );
        weightPoint_ = { x + 20, y + 20 };
    }
    else if ( type == "J" ) {
        for ( auto i = 0; i < 3; i++ ) {
            emit addSquareToScene(squares[i], {x + 20, y + i*20}, darkblue );
        }
        emit addSquareToScene( squares[3], {x , y + 40}, darkblue );
        weightPoint_ = { x + 20, y + 20 };
    }
    else if ( type == "L" ) {
        for ( auto i = 0; i < 3; i++ ) {
            emit addSquareToScene(squares[i], {x, y + i*20}, orange);
        }
        emit addSquareToScene( squares[3], {x + 20, y + 40}, orange );
        weightPoint_ = { x , y + 20 };
    }
    else if ( type == "S" ) {
        int index = 0;
        for ( auto i = 0; i < 2; i++ ) {
            for ( auto j = 0; j < 2; j++ ) {
                emit addSquareToScene(squares[index], {x + index*20 -i*20, y + 20 - i*20}, green);
                index++;
            }
        }
        weightPoint_ = { x + 20, y };
    }
    else if ( type == "Z" ) {
        int index = 0;
        for ( auto i = 0; i < 2; i++ ) {
            for ( auto j = 0; j < 2; j++ ) {
                emit addSquareToScene( squares[index], {x + index*20 - i*20, y + i*20}, red );
                index++;
            }
        }
        weightPoint_ = { x + 20, y };
    }
}

void Tetromino::setPlace()
{

}
