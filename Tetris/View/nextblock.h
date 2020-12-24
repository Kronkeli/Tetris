#ifndef NEXTBLOCKSCENE_H
#define NEXTBLOCKSCENE_H

#include "Model/tetromino.h"

#include <QGraphicsScene>

class NextBlock : public QGraphicsScene
{
    Q_OBJECT

public:
    NextBlock(QObject* parent = nullptr);

public slots:
    void updateNextBlock(int nextTetromino);
    void addSquareToScene(QGraphicsRectItem* square, QPointF coord, QBrush color);

};

#endif // NEXTBLOCKSCENE_H
