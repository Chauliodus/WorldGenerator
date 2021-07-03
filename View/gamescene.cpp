#include "gamescene.h"

Gamescene::Gamescene() : QGraphicsScene()
{
    // allow mouse games?
    isLndmShowing = false;
}

void Gamescene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (isLndmShowing) {
        isLndmShowing = false;
        emit sigLandmarkLeft();
        event->accept();
    } else QGraphicsScene::mousePressEvent(event);
}
