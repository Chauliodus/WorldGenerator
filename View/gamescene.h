#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "pixmapitem.h"

#include <QGraphicsScene>
#include <QObject>
#include <QWidget>
#include <QDebug>
#include <QGraphicsItemGroup>
#include <QGraphicsSceneMouseEvent>

class Gamescene : public QGraphicsScene
{
    Q_OBJECT
public:
    Gamescene();
    bool isLndmShowing;
    //QGraphicsItemGroup landmark_prev_group;
    QVector<PixmapItem *> landmark_item_list;
public slots:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
signals:
    void sigLandmarkLeft();
};

#endif // GAMESCENE_H
