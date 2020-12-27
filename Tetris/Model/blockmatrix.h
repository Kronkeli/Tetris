#ifndef BLOCKMATRIX_H
#define BLOCKMATRIX_H

#include <vector>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsView>

class blockMatrix: public QObject
{
    Q_OBJECT
public:
    blockMatrix();

    void addSquares(std::vector<QGraphicsRectItem*> squares);
    bool isSpaceAvailable(QPoint point);
    int checkRows();
    bool isRowComplete();
    void deleteRow(int rowNum);
    void clearData();

signals:

    void removeSquare(QGraphicsRectItem* item);

private:

    std::vector< std::vector< QGraphicsRectItem* > > blockMatrix_;

};

#endif // BLOCKMATRIX_H
