#ifndef TRAIL_H
#define TRAIL_H

#include <QObject>

#include <Model/landmark.h>

class Trail : public Landmark
{
    Q_OBJECT
public:
    Trail(WorldLevel * parent);
    virtual ~Trail(){}
    virtual void generateName();
    virtual void generateDescription();
    virtual void loadPicture();
public slots:
    virtual void research();
    virtual void destroy();
    virtual void get();
    virtual void onVisit();
};

#endif // TRAIL_H
