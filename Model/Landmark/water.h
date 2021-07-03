#ifndef WATER_H
#define WATER_H

#include <QObject>

#include <Model/landmark.h>

class Water : public Landmark
{
    Q_OBJECT
public:
    Water(WorldLevel * parent);
    virtual ~Water(){}
    virtual void generateName();
    virtual void generateDescription();
    virtual void loadPicture();
public slots:
    virtual void research();
    virtual void destroy();
    virtual void get();
    virtual void onVisit();
};

#endif // WATER_H
