#ifndef STATESCENE_H
#define STATESCENE_H

#include <QGraphicsScene>
#include <QObject>
#include <QWidget>
#include "pixmapitem.h"
#include <QGraphicsSceneMouseEvent>

class Statescene : public QGraphicsScene
{
    Q_OBJECT
public:
    Statescene();
    PixmapItem worldbutton;
    PixmapItem characteristics;
    PixmapItem inventory;
    PixmapItem physics;
    PixmapItem logic;
    PixmapItem ethics;
    PixmapItem willpower;
public slots:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

#endif // STATESCENE_H
