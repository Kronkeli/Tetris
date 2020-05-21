#ifndef NEXTBLOCKSCENE_H
#define NEXTBLOCKSCENE_H

#include "tetromino.h"

#include <QGraphicsScene>

class NextBlock : public QGraphicsScene
{
    Q_OBJECT

public:
    NextBlock(QObject* parent = nullptr);

public slots:
    void updateNextBlock(int nextTetromino);

};

#endif // NEXTBLOCKSCENE_H