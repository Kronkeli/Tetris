#include "blockmatrix.h"

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
//    qDebug() << "PISTEET Y: " << point.y() << "JA X: " << point.x();
    return blockMatrix_[point.y()][point.x()] == nullptr;
}

void blockMatrix::checkRows()
{
    qDebug() << "checkataan rivit ja tehdään juttuja";
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
//            for ( int row_up = row; row_up < 24; row_up++ ) {
//                for ( int column = 0; column < 12; column++ ) {
//                    blockMatrix_[row_up][column]->moveBy(0, 20);
//                }
//            }
//            for ( int column = 0; column < 12; column++ ) {
//                QGraphicsRectItem* square = blockMatrix_[row][column];
//                removeItem(square);
//                delete(square);
//            }

//            // Poistetaan valmiiden palojen ruudukosta tyhjä rivi ja asetetaan perään uusi tyhjä rivi
//            for ( auto row : completeRows ) {
//                for ()
//            }
////            completeRows.push_back(row);
////            for ( int column = 0; column < 12; column++ ) {

////                QGraphicsRectItem* square = blockMatrix_[row][column];
//////                blockMatrix_[row][column] = nullptr;
////                removeItem(square);
////                delete(square);

////            }
        }
    }
}

void blockMatrix::deleteRow(int rowNum)
{
    qDebug() << "deleteRow alussa rivillä: " << rowNum;

    // Siirretään muut palikat ylempänä alaspäin
    for ( int row_up = rowNum; row_up > 0; row_up-- ) {
        for ( int column = 0; column < 12; column++ ) {
            qDebug() << "mitä tapahtuu?";
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
