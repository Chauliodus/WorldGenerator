#ifndef MANMADE_H
#define MANMADE_H

#include <QObject>

#include <Model/landmark.h>

class Manmade : public Landmark
{
    Q_OBJECT
public:
    Manmade(WorldLevel * parent);
    virtual ~Manmade(){}
    virtual void generateName();
    virtual void generateDescription();
    virtual void loadPicture();

    int height;
public slots:
    virtual void research();
    virtual void destroy();
    virtual void get();
    virtual void onVisit();
};

#endif // MANMADE_H
