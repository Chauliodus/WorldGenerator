#ifndef LOCATION_H
#define LOCATION_H

#include "world.h"

#include <QObject>

class Location : public QObject
{
    Q_OBJECT
public:
    explicit Location(QObject *parent = nullptr);
    World * world;
    WorldLevel * level;
    Landmark * lndm;
    int world_num;
    int level_num;
    int landmark_num;
signals:

public slots:
};

#endif // LOCATION_H
