#ifndef WORLDLEVEL_H
#define WORLDLEVEL_H

#include "Model/landmark.h"
#include "Model/Landmark/item.h"
#include "Model/Landmark/building.h"
#include "Model/Landmark/realty.h"
#include "Model/Landmark/unit.h"
#include <Model/Landmark/manmade.h>
#include <Model/Landmark/mischance.h>
#include <Model/Landmark/trail.h>
#include <Model/Landmark/water.h>
#include <Model/Landmark/settlement.h>
#include <QPainter>
#include <QObject>
#include <QPixmap>

class World;

enum class Landscapes{
    CAVES,      PEAKS,            PLATEAU,
    HIGHLAND,   PLAIN,            LOWLAND,
    MATRIX,     MATRIX_1,         MATRIX_11,
    GLACIES,    ICE_WASTELAND,    MECH_FOREST,
    LIGHT,      SOUND,            VIBRO,
    OPEN_COSMO, BLACK_HOLE_ORBIT, STAR_CLUSTER
};

class WorldLevel : public QObject
{
    Q_OBJECT
public:
    explicit WorldLevel(World *parent = nullptr);
    ~WorldLevel();
    World * world_parent;
    QVector<Landmark *> landmark_list;
    QPixmap picture;
    QPixmap generatePicture();
    QString generateDescription();
    void generateLandmarks();
    int size;
    int number;
    QString description;
    Landscapes landscape;
signals:
public slots:
};

#endif // WORLDLEVEL_H
