#include "statepanel.h"

Statepanel::Statepanel(QWidget *parent) : QGraphicsView(parent)
{
    setMouseTracking(true);
    setMinimumSize(730, 80);
    setScene(&scene);
}
