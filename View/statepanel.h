#ifndef STATEPANEL_H
#define STATEPANEL_H

#include "statescene.h"
#include <QGraphicsView>
#include <QLabel>
#include <QWidget>

class Statepanel : public QGraphicsView
{
    Q_OBJECT
public:
    explicit Statepanel(QWidget *parent = nullptr);
    Statescene scene;
signals:

public slots:
};

#endif // STATEPANEL_H
