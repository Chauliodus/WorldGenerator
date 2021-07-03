#ifndef SETTLEMENT_H
#define SETTLEMENT_H

#include "Model/landmark.h"
#include <QDebug>
#include <QObject>
#include <Model/ideology.h>

class Settlement : public Landmark
{
    Q_OBJECT
public:
    Settlement(WorldLevel * parent);
    virtual ~Settlement(){}
    Ideology ideology;
    int size; // сколько народу может генерить это поселение
    // профессии
    // строения
    // видимость
    // укрепления
    virtual void generateName();
    virtual void generateDescription();
    virtual void loadPicture();
public slots:
    virtual void research();
    virtual void destroy();
    virtual void get();
    virtual void onVisit();
};

#endif // SETTLEMENT_H
