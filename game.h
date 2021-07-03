#ifndef GAME_H
#define GAME_H

#include "Model/hero.h"
#include "Model/world.h"
#include <iostream>
#include <QObject>
#include <Model/location.h>

/* Класс Game отвечает за основные игровые моменты, содержит уникальные на всю игру объекты,
 такие как "герой", "генератор" или "текущая локация". */

class Game : public QObject
{
    Q_OBJECT
public:
    explicit Game(QObject *parent = nullptr);
    ~Game(){}
    Location * curloc;
    World * generator;
    World * new_world;
    Hero * hero;
    QVector<Meeting *> meetings;

    void reactLndmChanged(Landmark *);
signals:
    void sigWorldCreated();
    void sigWorldChanged();
    void sigLevelChanged();
    void sigLandmarkChanged(Landmark *);
    void sigLandmarkAddedOnMap();
    void sigSendMessageToView(QString);
public slots:
    void createWorld();
    void researchWorld();
    void researchLevel();
    void increaseLvl();
    void decreaseLvl();
    void selectLandmark(Landmark *);
    void addOnMap();
    void addItemToInventory(Item *);
    void isItemInStock(Resource *);
    void unitMet(Unit *);
};

#endif // GAME_H
