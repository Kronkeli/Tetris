#include "Model/blockmatrix.h"

#include <vector>
#include <QGraphicsRectItem>
#include <QDebug>

blockMatrix::blockMatrix()
{
    std::vector<QGraphicsRectItem*> row;
    for ( int rowNum = 0; rowNum < 25; rowNum++ ) {
        for ( int columnNum = 0; columnNum < 12; columnNum++ ) {
            row.push_back( nullptr );
        }
        blockMatrix_.push_back(row);
        row.clear();
    }
}

void blockMatrix::addSquares(std::vector<QGraphicsRectItem*> squares )
{
    int yPos;
    int xPos;
    for ( QGraphicsRectItem* square : squares ) {
        yPos = ( (int)square->y() ) / 20;
        xPos = ( (int)square->x() ) / 20;
        blockMatrix_[yPos][xPos] = square;
    }
}

bool blockMatrix::isSpaceAvailable(QPoint point)
{
    return blockMatrix_[point.y()][point.x()] == nullptr;
}

void blockMatrix::checkRows()
{
    bool rowComplete;
    std::vector<int> completeRows;

    for ( int row = 0; row < 24; row++ ) {
        rowComplete = true;
        for ( int column = 0; column < 12; column++ ) {
            if ( blockMatrix_[row][column] == nullptr) {
                rowComplete = false;
            }
        }
        if ( rowComplete ) {
            deleteRow(row);
        }
    }
}

void blockMatrix::deleteRow(int rowNum)
{

    // Siirretään muut palikat ylempänä alaspäin
    for ( int row_up = rowNum; row_up > 0; row_up-- ) {
        for ( int column = 0; column < 12; column++ ) {
            if ( blockMatrix_[row_up][column] != nullptr ) {
                blockMatrix_[row_up][column]->moveBy(0,20);
            }
        }
    }
    // Poistetaan vanha rivi ja luodaan samalla uusi nullptr täyteinen tilalle
    auto begin = blockMatrix_.begin();
    for ( int column = 0; column < 12; column++ ) {
        QGraphicsRectItem* square = blockMatrix_[rowNum][column];
        emit removeSquare(square);
        delete(square);
    }
        blockMatrix_.erase( begin+rowNum );
        std::vector<QGraphicsRectItem*> row;
        for ( int column = 0; column < 12; column++ ) {
            row.push_back(nullptr);
        }
        blockMatrix_.insert(begin, row);
}

void blockMatrix::clearData()
{
    QGraphicsRectItem* squarePtr;
    for ( int rowNum = 0; rowNum < 25; rowNum++ ) {
        for ( int columnNum = 0; columnNum < 12; columnNum++ ) {
            squarePtr = blockMatrix_[rowNum][columnNum];
            if ( squarePtr != nullptr ) {
                emit removeSquare(squarePtr);
                delete(squarePtr);
                blockMatrix_[rowNum][columnNum] = nullptr;
            }
        }
    }
}
