#include "nextblock.h"

#include <QDebug>

NextBlock::NextBlock(QObject* parent):
    QGraphicsScene(parent)
{
}

void NextBlock::updateNextBlock(int nexttetromino)
{
    qDebug() << nexttetromino;
}
