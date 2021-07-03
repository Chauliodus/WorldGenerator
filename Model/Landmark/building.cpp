#include "Model/Landmark/building.h"
#include "Model/worldlevel.h"
#include "Model/world.h"

Building::Building(WorldLevel * parent) : Landmark(parent)
{
    type = LndmType::BUILDING;
    loadPicture();
    generateName();
    generateDescription();
    isCanBeAddedOnMap = 1;
    isSeenFromAfar = 0;
    isAddedOnMap = 0;
    // если урбанизация больше нуля, то этажность будет от нуля до урбанизации (убрать ветвление нельзя - деление на ноль)
    if (wlevel_parent->world_parent->urbanisation > 0)
        storeys = rand()%wlevel_parent->world_parent->urbanisation; // нулевая этажность означает землянку или нору.
    bool landscape_pass = (parent->landscape == Landscapes::PLATEAU) ||
                          (parent->landscape == Landscapes::ICE_WASTELAND) ||
                          (parent->landscape == Landscapes::OPEN_COSMO);
    // если этажность больше природы, а ландшафт - плато, равнины, пустоши или открытый космос, то строение видно издалека.
    if (storeys > wlevel_parent->world_parent->nature && landscape_pass) {
        isSeenFromAfar = true;
    }
    get_string = "Зайти";
}
void Building::generateName()
{
    int a = rand()%3;
    switch (a) {
        case 0 : name = "Дом"; break;
        case 1 : name = "Хижина"; break;
        case 2 : name = "Дворец"; break;
    }
}
void Building::generateDescription()
{
    description = "Это здание видало лучшие времена.";

    /* Вы приближаетесь к жилищу местной фауны. Вокруг валяются обглоданные кости, обрывки эктоплазы,
     * отголоски астральных сущностей, обломки металла и пластика...

       Когда враг будет уничтожен, на месте его логова можно обустроить склад, мастерскую или тюрьму для рабов. */
}

void Building::loadPicture()
{
    picture.load("../res/buildings/living.png");
    picture_preview.load("../res/buildings/living_preview.png");
    picture_preview_hovered.load("../res/buildings/living_preview_hovered.png");
}

void Building::onVisit()
{
    actions.clear();
    actions.push_back(new QPair<QString, QString>("Осмотреть", "research"));
    actions.push_back(new QPair<QString, QString>("Наблюдать", "research"));
    actions.push_back(new QPair<QString, QString>("Постучать", "get"));
    actions.push_back(new QPair<QString, QString>("Скрытно пробраться", "get"));
    actions.push_back(new QPair<QString, QString>("Штурмовать", "get"));
    actions.push_back(new QPair<QString, QString>("Сжечь", "destroy"));
}
void Building::research()
{
    qDebug() << name << " " << description;
}
void Building::get()
{
    qDebug() << "Get" << name << " " << description;
}
void Building::destroy()
{

}
