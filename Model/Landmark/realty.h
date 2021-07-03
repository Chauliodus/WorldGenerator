#ifndef REALTY_H
#define REALTY_H

#include "Model/landmark.h"
#include <Model/resource.h>
#include "item.h"
#include <QDebug>
#include <QObject>

enum class SourceType{
    NOT_A_REALTY,
    BUSH,
    TREE,
    MEADOW,
    MINE,
    MAX_REALTY
};

enum class Resources{ // ПОЗЖЕ БУДЕТ СВИТЧЕВАТЬСЯ ПРИ ГЕНЕРАЦИИ КОНКРЕТНОГО ИСТОЧНИКА
    not_a_res,
    roses,
    coffee,
    pepper,
    ginger,
    word,
    melody,
    enegry_rock,
    meat,
    iron_tree,
    sweet_grass,
    ice_grass,
    honey,
    one,
    two,
    three,
    max_res
};

class Realty : public Landmark
{
    Q_OBJECT
public:
    Realty(WorldLevel * parent);
    virtual ~Realty(){}
    SourceType sourceType;
    bool renewable; // что насчет разных ресурсов? Пример: плоды на дереве возобновимы, а бревна - нет
    QMap<QString, Resource *> resources;


    // для грибниц:
    // int зрелость
    // int урожаев в цикле
    // int количество сборов
    // int дней в цикле
    // int текущий день цикла
    // int количество спор
    // int выживаемость спор
    // int требования к почве

    virtual void generateName();
    virtual void generateDescription();
    virtual void loadPicture();
signals:
public slots:
    virtual void research();
    virtual void destroy();
    virtual void get();
    virtual void onVisit();
    void f1();
    void f2();
    void f3();
    void f4();
    void f5();
    void f6();
    void f7();
    void f8();
    void f9();
    void f10();

};

#endif // REALTY_H
