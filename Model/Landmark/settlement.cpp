#include "settlement.h"

Settlement::Settlement(WorldLevel * parent) : Landmark(parent)
{
    type = LndmType::SETTLEMENT;
    loadPicture();
    generateName();
    generateDescription();
    isSeenFromAfar = 1;
    isAddedOnMap = 0;
    isCanBeAddedOnMap = 1;
    get_string = "Войти";
}
void Settlement::generateName()
{
    int a = rand()%5;
    switch (a) {
        case 0 : name = "Лагерь"; break;
        case 1 : name = "Деревня"; break;
        case 2 : name = "Городок"; break;
        case 3 : name = "Город"; break;
        case 4 : name = "Мегаполис"; break;
    }
}
void Settlement::generateDescription()
{
    description = "Поселение неких существ";
}

void Settlement::loadPicture()
{
    picture.load("../res/settlementes/city.png");
    picture_preview.load("../res/settlementes/city_preview.png");
    picture_preview_hovered.load("../res/settlementes/city_preview_hovered.png");
}
void Settlement::research()
{
    qDebug() << name << " " << description;

}
void Settlement::get()
{
    qDebug() << "Get" << name << " " << description;
}

void Settlement::onVisit()
{
    actions.clear();
    actions.push_back(new QPair<QString, QString>("Осмотреть", "research"));
    actions.push_back(new QPair<QString, QString>("Наблюдать", "research"));
    actions.push_back(new QPair<QString, QString>("Войти", "research"));
    actions.push_back(new QPair<QString, QString>("Скрытно пробраться", "research"));
    actions.push_back(new QPair<QString, QString>("Штурмовать", "research"));
    actions.push_back(new QPair<QString, QString>("Сжечь", "destroy"));
}
void Settlement::destroy()
{

}
