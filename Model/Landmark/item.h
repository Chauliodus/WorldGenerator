#ifndef ITEM_H
#define ITEM_H

#include "Model/landmark.h"
#include <QDebug>
#include <QObject>

class Item : public Landmark
{
    Q_OBJECT
public:
    Item();
    Item(Item *);
    Item(WorldLevel * parent);
    virtual ~Item(){}

    Landmark * parent;
    //int count;
    bool isInInventory = false;

    void createRandomItem();

public slots:
    virtual void research();
    virtual void destroy();
    virtual void get();
    virtual void onVisit();
};

#endif // ITEM_H
