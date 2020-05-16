#include "tetromino.h"

#include <QGraphicsScene>
#include <QRandomGenerator>
#include <QDebug>
#include <set>
#include <QMainWindow>
#include <iostream>

Tetromino::Tetromino()
{
}

void Tetromino::moveDown()
{
    for ( auto square : squares ) {
        square->moveBy(0,20);
    }
    weightPoint_.setY( weightPoint_.y() + 20 );
    qDebug() << weightPoint_.y();
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
    std::string juu = "orientaatio: " + ORIENTATION[orientation_];
    qDebug() << QString::fromStdString(juu);
    for ( QGraphicsRectItem* square : squares ) {
        dx = weightPoint_.x() - square->x();
        dy = weightPoint_.y() - square->y();
        std::string orient = ORIENTATION[orientation_];
        if ( orient == "UP" ) {
            square->setX( weightPoint_.x() + dy );
            square->setY( weightPoint_.y() - dx );
        }
        else if ( orient == "RIGHT" ) {
            square->setX( weightPoint_.y() + dy );
            square->setY( weightPoint_.x() - dx );
        }
        else if ( orient == "DOWN" ) {
            square->setX( weightPoint_.x() + dy);
            square->setY( weightPoint_.x() - dx);
        }
        else if ( orient == "LEFT") {
            square->setX( weightPoint_.x() + dy );
            square->setY( weightPoint_.y() - dx );
        }

    }
    orientation_ = ( orientation_ + 1 ) % 4;
}

void Tetromino::setType(int number)
{
    std::string type = TETROMINOS[number];

    for ( int i = 0; i < 4; i++ ) {
        squares.push_back( new QGraphicsRectItem(0, 0, SIZE, SIZE) );
    }
    orientation_ = 0;
    if ( type == "I" ) {
        for ( int i = 0; i < 4; i++ ) {
            emit addSquare(squares[i], {100 + i*20, 0}, blue);
        }
        weightPoint_ = {110, 30};
    }
    else if ( type == "O" ) {
        int index = 0;
        for ( int i = 0; i < 2; i++ ) {
            for ( int j = 0; j < 2; j++ ) {
                emit addSquare(squares[index], {120 + i*20, j*20}, yellow);
                index++;
            }
        }
        weightPoint_ = { 130, 10 };
    }
    else if ( type == "T" ) {
        for ( auto i = 0; i < 3; i++ ) {
            emit addSquare(squares[i], {120 + i*20, 0}, purple);
        }
        emit addSquare( squares[3], {140, 20}, purple );
    }
    else if ( type == "J" ) {
        for ( auto i = 0; i < 3; i++ ) {
            emit addSquare(squares[i], {140, i*20}, darkblue );
        }
        emit addSquare( squares[3], {120, 40}, darkblue );
    }
    else if ( type == "L" ) {
        for ( auto i = 0; i < 3; i++ ) {
            emit addSquare(squares[i], {140, i*20}, orange);
        }
        emit addSquare( squares[3], {160, 40}, orange );
    }
    else if ( type == "S" ) {
        int index = 0;
        for ( auto i = 0; i < 2; i++ ) {
            for ( auto j = 0; j < 2; j++ ) {
                emit addSquare(squares[index], {140 + index*20 -i*20, 20 - i*20}, green);
                index++;
            }
        }
    }
    else if ( type == "Z" ) {
        int index = 0;
        for ( auto i = 0; i < 2; i++ ) {
            for ( auto j = 0; j < 2; j++ ) {
                emit addSquare( squares[index], {140 + index*20 - i*20, i*20}, red );
            }
        }
    }
}

void Tetromino::setPlace()
{

}
