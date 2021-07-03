#include "pixmapitem.h"

PixmapItem::PixmapItem(QPixmap * pic, QObject * parent)
    : QObject(parent), QGraphicsPixmapItem()
{
    setPixmap(*pic);
}

PixmapItem::PixmapItem(Landmark * lndm, QObject * parent)
    : QObject(parent), QGraphicsPixmapItem(), lndm(lndm)
{
    type = PixmapItemTypes::LANDMARK;
    setAcceptHoverEvents(true);
    setPixmap(lndm->picture_preview);
}

void PixmapItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    if (type == PixmapItemTypes::LANDMARK)
        if (!hovered) {
            hovered = true;
            setPixmap(lndm->picture_preview_hovered);
            setToolTip(lndm->tooltip);
        }
    if (statebutton == StateButtons::INV)
        if (!hovered) {
            hovered = true;
            QPixmap p22("../res/statepanel/inventory_hovered.png");
            setPixmap(p22);
        }
    if (statebutton == StateButtons::WINFO)
        if (!hovered) {
            hovered = true;
            QPixmap p22("../res/statepanel/worldinfo_hovered.png");
            setPixmap(p22);
        }
    if (statebutton == StateButtons::CHAR)
        if (!hovered) {
            hovered = true;
            QPixmap p22("../res/statepanel/characteristics_hovered.png");
            setPixmap(p22);
        }
}

void PixmapItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    if (type == PixmapItemTypes::LANDMARK)
        if (hovered){
            hovered = false;
            setPixmap(lndm->picture_preview);
        }
    if (statebutton == StateButtons::INV)
        if (hovered) {
            hovered = false;
            QPixmap p22("../res/statepanel/inventory.png");
            setPixmap(p22);
        }
    if (statebutton == StateButtons::WINFO)
        if (hovered) {
            hovered = false;
            QPixmap p22("../res/statepanel/worldinfo.png");
            setPixmap(p22);
        }
    if (statebutton == StateButtons::CHAR)
        if (hovered) {
            hovered = false;
            QPixmap p22("../res/statepanel/characteristics.png");
            setPixmap(p22);
        }
}

void PixmapItem::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if (type == PixmapItemTypes::LANDMARK){
        emit sigLandmarkSelected(lndm);
    }
    if (statebutton == StateButtons::CHAR){
        qDebug() << "1 1 1 1";
    }
    if (statebutton == StateButtons::INV){
        //qDebug() << "inventory";
        emit sigOpenInventory();
    }
    if (statebutton == StateButtons::WINFO){
        qDebug() << "red green blue";
    }
}
