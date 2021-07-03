#include "gamefield.h"


Gamefield::Gamefield(QWidget *parent) : QGraphicsView(parent)
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // Отключим скроллбар по горизонтали
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);   // Отключим скроллбар по вертикали
    setMinimumSize(730, 380);
    setScene(&scene);

    QPixmap p("../res/menu.png");
    scene.addPixmap(p);
}

void Gamefield::setPicture(QPixmap & pic)
{
    scene.addPixmap(pic);
}

//void Gamefield::mousePressEvent(QMouseEvent *event)
//{
//    QGraphicsView::mousePressEvent(event);
//}

