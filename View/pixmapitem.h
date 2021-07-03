#ifndef LANDMARKLABEL_H
#define LANDMARKLABEL_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QDebug>
#include <qgraphicsitem.h>

#include <Model/landmark.h>

enum class PixmapItemTypes {
    LANDMARK,
    ACTION_BUTTON,
    STATE_PANEL_BUTTON,
    INVENTORY_ITEM
};

enum class StateButtons {
    NOT_A_BUTTON,
    WINFO,
    CHAR,
    INV,
    PHYS,
    LOG,
    ETH,
    WPOW
};

class PixmapItem : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    PixmapItem(){ setAcceptHoverEvents(true); }
    PixmapItem(QPixmap *, QObject * parent = nullptr);
    PixmapItem(Landmark * l, QObject * parent = nullptr);
    ~PixmapItem(){}
    PixmapItemTypes type;
    StateButtons statebutton;
    Landmark * lndm;
    bool hovered;
signals:
    void sigLandmarkSelected(Landmark *);
    void sigLandmarkLeft();
    void sigOpenInventory();
public slots:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
};

#endif // LANDMARKLABEL_H
