#ifndef MISCHANCE_H
#define MISCHANCE_H

#include <QObject>

#include <Model/landmark.h>

class Mischance : public Landmark
{
    Q_OBJECT
public:
    Mischance(WorldLevel * parent);
    virtual ~Mischance(){}
    virtual void generateName();
    virtual void generateDescription();
    virtual void loadPicture();

public slots:
    virtual void research();
    virtual void destroy();
    virtual void get();
    virtual void onVisit();
};

#endif // MISCHANCE_H
