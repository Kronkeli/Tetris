#ifndef SQUARE_H
#define SQUARE_H

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <set>
#include <map>
#include <vector>
#include <QPoint>

const QPen black(Qt::black);
const QBrush blue(Qt::blue);
const QBrush darkblue(Qt::darkBlue);
const QBrush orange(Qt::darkYellow);
const QBrush yellow(Qt::yellow);
const QBrush green(Qt::green);
const QBrush purple(Qt::magenta);
const QBrush red(Qt::red);

const int SIZE = 20;

const std::vector<std::string> TETROMINOS {
    "I",
    "O",
    "T",
    "J",
    "L",
    "S",
    "Z"
};

class Tetromino : public QObject
{
    Q_OBJECT
public:
    Tetromino(QPointF coordinate);
    void setType(int number);
    void setPlace();
    void moveDown();
    void moveLeft(int amount = 1);
    void moveRight(int amount = 1);
    void tetrominoTurn(int direction = 1);
    QPointF getWeightPoint();

    std::vector<QGraphicsRectItem*> squares;


signals:
    void addSquareToScene(QGraphicsRectItem* square, QPointF coord, QBrush color);
    void blockStopped();

private:

    QPointF weightPoint_;
    QPointF pointOfCreation_;
};

#endif // SQUARE_H
