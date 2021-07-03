#ifndef UNIT_H
#define UNIT_H

#include "Model/landmark.h"
#include "item.h"
#include <QDebug>
#include <QObject>
#include <Model/meeting.h>

enum class Race{
    NOT_A_UNIT,
    DEMON, // крылатый демон, приносящий страдания - или мелкий пакостник
    DEVIL, // крылатый демон, приносящий страдания - или мелкий пакостник
    IFRIT, // могучий огненный дух
    MELODY, // живая мелодия
    GOLEM, // голем
    DWARF, // карл
    PRINCESS, // взбалмошное порождение природы
    HULDRE, // хюльдра
    PAN, // пан
    ICE_DEVIL, // ледянной демон
    NECROMANCER, // некромант
    VAMPIRE, // вампир
    UNDEAD, // нежить
    BANSHIE, // ледяной дух
    ROBO, // робот
    CODE, // живой программный код (program?)
    VIRUS, // программный вирус
    SPIRIT, // астральная сущность
    FAIRY, // волшебное существо
    ALIEN, // инопланетянин (фиолетовый осьминог)
    MAX_UNIT
};

class Unit : public Landmark
{
    Q_OBJECT
public:
    Unit(WorldLevel * parent);
    Unit(Unit *);
    virtual ~Unit(){}
    virtual void generateName();
    virtual void generateDescription();
    virtual void loadPicture();
    WorldLevel * parent;
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
    int suffering; // своеобразный ресурс. Ингридиент для магии, зелий, цвета, пища некоторых существ. Ну, и штраф, конечно
    int pride; // коэфф. скорости роста доминирования, и множитель страдания за потеряю доминирования

    void createRandomUnit();
signals:

public slots:
    virtual void research();
    virtual void destroy();
    virtual void get();
    virtual void onVisit();
    void sayHello();
};

#endif // UNIT_H
