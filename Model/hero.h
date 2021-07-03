#ifndef HERO_H
#define HERO_H
#include "Model/Landmark/item.h"
#include "Model/world.h"

#include <QObject>

#include <Model/Landmark/unit.h>

class Hero : public QObject
{
    Q_OBJECT
public:
    explicit Hero(QObject *parent = nullptr);
    ~Hero(){}
    int willpower;
    int logic;
    int physic;
    int ethic;
    QVector<Item *> inventory;
    QVector<Unit *> cameraden;
    QVector<QString> marks;
    Meeting * meeting;
    int stealth;
    int attention;
    int domination;
signals:
    void sigItemAddingToInventory(Item *);

public slots:
};

#endif // HERO_H
