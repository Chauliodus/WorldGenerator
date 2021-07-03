#include "manmade.h"
#include "Model/worldlevel.h"
#include "Model/world.h"

Manmade::Manmade(WorldLevel * parent) : Landmark(parent)
{
    type = LndmType::MANMADE;
    loadPicture();
    generateName();
    generateDescription();
    isSeenFromAfar = 0;
    isAddedOnMap = 0;
    isCanBeAddedOnMap = 1;
    int urb = 1, nat = 1;
    if (wlevel_parent->world_parent->urbanisation > 2)
        urb = wlevel_parent->world_parent->urbanisation / 2;
    if (wlevel_parent->world_parent->nature > 2)
        nat = wlevel_parent->world_parent->nature / 2;
    if (urb || nat)
        height = rand()%urb + rand()%nat;
    if (height > wlevel_parent->world_parent->nature ||
            height > wlevel_parent->world_parent->urbanisation){
        isSeenFromAfar = true;
    }
}
void Manmade::generateName()
{
    int a = rand()%3;
    switch (a) {
        case 0 : name = "Статуя"; break;
        case 1 : name = "Гнездо"; break;
        case 2 : name = "Фрактальный камень"; break;
    }
}
void Manmade::generateDescription()
{
    description = "Таинственный объект, явно рукотворный... или ноготворный...";
}

void Manmade::loadPicture()
{
    picture.load("../res/manmaids/statue.png");
    picture_preview.load("../res/manmaids/statue_preview.png");
    picture_preview_hovered.load("../res/manmaids/statue_preview_hovered.png");
}

void Manmade::onVisit()
{
    actions.clear();
    actions.push_back(new QPair<QString, QString>("Воздать хвалу", "get"));
    actions.push_back(new QPair<QString, QString>("Наблюдать", "research"));
    actions.push_back(new QPair<QString, QString>("Исследовать", "research"));
    actions.push_back(new QPair<QString, QString>("Разрушить", "destroy"));
}
void Manmade::research()
{
    qDebug() << name << " " << description;

}
void Manmade::get()
{
    qDebug() << "Get" << name << " " << description;
}
void Manmade::destroy()
{

}
