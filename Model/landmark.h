#ifndef LANDMARK_H
#define LANDMARK_H

#include "resource.h"

#include <QPainter>
#include <QObject>
#include <QDebug>

class WorldLevel;
class UserAction;
class Item;
class Unit;

enum class LndmType{
    ITEM,
    BUILDING,
    UNIT,
    REALTY,
    MANMADE,
    WATER,
    TRAIL,
    MISCHANCE,
    SETTLEMENT
};

class Landmark : public QObject
{
    Q_OBJECT
public:
    explicit Landmark(){}
    Landmark(Landmark *);
    Landmark(WorldLevel * wlevel_parent);
    virtual ~Landmark(){}
    virtual void generateName(){}
    virtual void generateDescription(){}
    virtual void loadPicture(){}

    WorldLevel * wlevel_parent;
    LndmType type;
    QString name;
    QString description;
    QString picture_name;
    QPixmap picture;
    QPixmap picture_preview;
    QPixmap picture_preview_hovered;
    int number;
    int x;
    int y;
    QVector<QPair<QString,QString>*> actions;
    //<QString, QString> sdf;


    //Union owner;
    bool isSeenFromAfar;
    bool isAddedOnMap;
    bool isCanBeAddedOnMap;
    
    int max_resource;
    int count; // сколько доступно для сбора
    int steals; // скрытность. Спрятанные сокровища, скрытые лаборатории, военные полигоны и прочая роскошь

    QString get_string;
    QString research_string;
    QString destroy_string;
    QString tooltip;
signals:
    void sigItemAddingToInventory(Item*);
    virtual void sigIsItemInStack(Resource * res);
    virtual void sigUnitMet(Unit *);
public slots:
    virtual void research();
    virtual void get();
    virtual void destroy();
    virtual void onVisit(){}
};

#endif // LANDMARK_H
