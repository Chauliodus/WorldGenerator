#include "Model/Landmark/item.h"
#include "Model/worldlevel.h"
#include "Model/world.h"

Item::Item() : Landmark()
  // конструктор по умолчанию для создания минимально описанного предмета. Используется для realties - при генер.ресурсов.
{
    type = LndmType::ITEM;
    isSeenFromAfar = 0;
    isAddedOnMap = 0;
    isCanBeAddedOnMap = 0;
    count = 1;
    parent = nullptr;
}

Item::Item(Item * source) : Landmark() // конструктор копирования для помещения предметов в рюкзак
{
    type = source->type;
    count = source->count;
    name = source->name;
    description = source->description;
    picture_name = source->picture_name;
    picture = source->picture;
    picture_preview = source->picture_preview;
    picture_preview_hovered = source->picture_preview_hovered;
    //actions = source->actions;
    parent = source->parent;

    //owner = source->owner;
    isSeenFromAfar = source->isSeenFromAfar;
    isAddedOnMap = source->isAddedOnMap;
    isCanBeAddedOnMap = source->isCanBeAddedOnMap;

    //steals = source->steals;
}

Item::Item(WorldLevel * parent) : Landmark(parent) // конструктор для генерации предмета на земле (как лндм, на волдлевеле)
{
    type = LndmType::ITEM;
    createRandomItem();
    isSeenFromAfar = 0;
    isAddedOnMap = 0;
    isCanBeAddedOnMap = 0;
    count = 1;
}

void Item::onVisit()
{
    actions.clear();
    actions.push_back(new QPair<QString, QString>("Подобрать", "get"));
    actions.push_back(new QPair<QString, QString>("Осмотреть", "осмотреть"));
    actions.push_back(new QPair<QString, QString>("Выбросить", "destroy"));
}

void Item::createRandomItem()
{
    QString picname;
    int a = rand()%3;
    switch (a) {
        case 0 : {
            name = "Меч";
            description = "Превосходный меч деревянной стали, безупречно тупой, восхитительно трухлявый. "
                   "Должно быть, он стоит баснословных грошей!";
            picname = "sword";
            break;
        }
        case 1 : {
            name = "Топор";
            description = "Крепкий топор какого-то дровосека.";
            picname = "axe";
            break;
        }
        case 2 : {
            name = "Трава";
            description = "Пучок волшебной травы. Даже если она не научит вас дышать огнем или двигать горы взглядом, то "
                          "в супе будет поистине вкусна.";
            picname = "grass";
            break;
        }
    }
    count = 1;
    get_string = "Подобрать";
    picture.load("../res/items/" + picname + ".png");
    picture_preview.load("../res/items/" + picname + "_preview.png");
    picture_preview_hovered.load("../res/items/" + picname + "_preview_hovered.png");
}
void Item::research()
{
    qDebug() << name << " " << description;
}
void Item::get()
{
    qDebug() << "Вы забираете " << count << name << " с собой.";
    Item * copy = new Item(this);
    emit sigItemAddingToInventory(copy);
    createRandomItem();
}
void Item::destroy()
{
    qDebug() << "уничтожить предмет.";
}
