#include "mischance.h"
#include "Model/worldlevel.h"
#include "Model/world.h"

Mischance::Mischance(WorldLevel * parent) : Landmark(parent)
{
    type = LndmType::MISCHANCE;
    loadPicture();
    generateName();
    generateDescription();
    isSeenFromAfar = 0;
    isAddedOnMap = 0;
    isCanBeAddedOnMap = 0;
    get_string = "NULL";
}
void Mischance::generateName()
{
    int a = rand()%3;
    switch (a) {
        case 0 : name = "Гроза"; break;
        case 1 : name = "Укус змеи"; break;
        case 2 : name = "Подвернутая нога"; break;
    }
}
void Mischance::generateDescription()
{
    description = "С вами происходит несчастье. Кажется, вам тут не рады";
}

void Mischance::loadPicture()
{
    picture.load("../res/mischances/storm.png");
    picture_preview.load("../res/mischances/storm_preview.png");
    picture_preview_hovered.load("../res/mischances/storm_preview_hovered.png");
}
void Mischance::research()
{
    qDebug() << name << " " << description;

}
void Mischance::get()
{
    qDebug() << "Get" << name << " " << description;
}

void Mischance::onVisit()
{

}
void Mischance::destroy()
{

}
