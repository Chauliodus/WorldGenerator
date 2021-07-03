#ifndef BUILDING_H
#define BUILDING_H

#include "Model/landmark.h"
#include <QDebug>
#include <QObject>

class WorldLevel;

// жилой дом (стоянка, лагерь, хутор, хибара, дом, усадьба, дворец ... капсула)
// логово (пещера, улей, ... гнездо)
// руины
// служебное помещение (школа, заправка, рудник (именно рукотворный), гостиница ...)

class Building : public Landmark
{
    Q_OBJECT
public:
    Building(WorldLevel * parent);
    virtual ~Building(){}
    virtual void generateName();
    virtual void generateDescription();
    virtual void loadPicture();
    int storeys; // этажность. Влияет, видится ли объект издалека (на карте)
    // идеология, принадлежность
    // вместительность - 10, 50, 100, 200, 500
    // фортификации - 0 - отсутствуют. 1 - частокол. 2 - бревенчатые стены. 3 - каменные стены. 4 - бетонный бункер. 5 - силовые поля.
    // Могут понадобиться катапульты, рытье подкопа, взрывчатка, проход сквозь стену ("камень в туман"),
    // искажение пространства, полет

public slots:
    virtual void research();
    virtual void destroy();
    virtual void get();
    virtual void onVisit();
};

#endif // BUILDING_H
