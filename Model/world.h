#ifndef WORLD_H
#define WORLD_H

#include "Model/worldlevel.h"
#include <QObject>
#include <QPixmap>
#include <QString>
#include <QPainter>

enum class Fractions{
    RED,
    GREEN,
    BLUE,
    CYAN,
    YELLOW,
    MAGENTA
};

class World : public QObject
{
    Q_OBJECT
public:
    explicit World(QObject *parent = nullptr);
    World(bool);
    virtual ~World();
    QPixmap generatePicture();
    void generateName();
    QString generateDescription();

    int agressy;
    int fraction;
    int power;
    int urbanisation;
    int nature;
    int techlevel;
    int size;
    QString name;
    QString description;
    Fractions color;
    QPixmap picture;
    QVector<WorldLevel *> level_list;
signals:
    void sigItemCreated_from_world(Item *);
    void sigIsInStock_from_world(Resource *);
    void sigUnitMet_from_world(Unit *);
public slots:
    void catchedItemCreatedSig(Item *);
    void catchedIsInStockSig(Resource *);
    void catchedUnitMetSig(Unit *);
};

#endif // WORLD_H
