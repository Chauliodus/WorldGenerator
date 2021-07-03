#include "trail.h"
#include "Model/worldlevel.h"
#include "Model/world.h"

Trail::Trail(WorldLevel * parent) : Landmark(parent)
{
    type = LndmType::TRAIL;
    loadPicture();
    generateName();
    generateDescription();
    isSeenFromAfar = 0;
    isAddedOnMap = 0;
    isCanBeAddedOnMap = 1;
    get_string = "Следовать";
}
void Trail::generateName()
{
    int a = rand()%3;
    switch (a) {
        case 0 : name = "Старая дорога"; break;
        case 1 : name = "Животная тропа"; break;
        case 2 : name = "Хайвей ту хелл"; break;
    }
}
void Trail::generateDescription()
{
    description = "Дорога, ведущая в никуда";
}

void Trail::loadPicture()
{
    picture.load("../res/trails/road.png");
    picture_preview.load("../res/trails/road_preview.png");
    picture_preview_hovered.load("../res/trails/road_preview_hovered.png");
}
void Trail::research()
{
    qDebug() << name << " " << description;

}
void Trail::get()
{
    qDebug() << "Get" << name << " " << description;
}

void Trail::onVisit()
{
    actions.clear();
    actions.push_back(new QPair<QString, QString>("Осмотреть", "research"));
    actions.push_back(new QPair<QString, QString>("Наблюдать", "research"));
    actions.push_back(new QPair<QString, QString>("Следовать", "research"));
    actions.push_back(new QPair<QString, QString>("Устроить засаду", "research"));
    actions.push_back(new QPair<QString, QString>("Послать разведчиков", "research"));
    actions.push_back(new QPair<QString, QString>("Взорвать", "destroy"));
}
void Trail::destroy()
{

}
