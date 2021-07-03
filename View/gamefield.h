#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include "gamescene.h"
#include "pixmapitem.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItemGroup>
#include <QLabel>
#include <QWidget>

class Gamefield : public QGraphicsView
{
    Q_OBJECT
public:
    explicit Gamefield(QWidget *parent = nullptr);
    Gamescene scene;

    void setPicture(QPixmap &);
signals:

public slots:
    //void mousePressEvent(QMouseEvent *event);
};

#endif // GAMEFIELD_H
