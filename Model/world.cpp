#include "Model/world.h"


World::World(QObject *parent) : QObject(parent) // Создает мир вместе с уровнями и, след-но, ландмарками
{
    agressy = rand()%6;
    nature = rand()%6;
    power = rand()%6;
    fraction = rand()%6;
    urbanisation = rand()%6;
    techlevel = rand()%6;
    size = rand()%26 + 3;
    if (fraction == 0) color = Fractions::RED;
    if (fraction == 1) color = Fractions::GREEN;
    if (fraction == 2) color = Fractions::BLUE;
    if (fraction == 3) color = Fractions::CYAN;
    if (fraction == 4) color = Fractions::YELLOW;
    if (fraction == 5) color = Fractions::MAGENTA;
    generateName();
    generatePicture();
    description = generateDescription();
    level_list.clear();
    for(int i = 0; i < size; i++){
        level_list.push_back(new WorldLevel(this));
        level_list.last()->number = i;
    }
}

World::World(bool) // создает генератор миров, bool на вход - для отличения констр-в один от другого
{
    agressy = 0;
    nature = 0;
    fraction = 6;
    power = 0;
    urbanisation = 0;
    size = 0; // количество сохраненных миров
    name = "Генератор миров";
    description = "Вы находитесь в странном месте - в генераторе миров.\n"
                    "Сейчас он не защитит вас от нападения врагов.\n"
                    "Здесь невозможно поддерживать жизнь.\n"
                    "Генератор лишен магической мощи.\n"
                    "Здесь нельзя разместить последователей.\n"
                    "Нельзя запоминать миры.";
    picture.load("../res/generator.png");
}

World::~World()
{
    for(int i = 0; i < size; i++){
        delete level_list[i];
    }
}

QPixmap World::generatePicture()
{
    int WIDTH = 730, HIGHT = 380;
    QImage sky_img("../res/back.png");
    QImage fraction_img(QSize(WIDTH, HIGHT), QImage::Format_ARGB32);
    if (fraction == 0) fraction_img.fill(Qt::GlobalColor::red);
    if (fraction == 1) fraction_img.fill(Qt::GlobalColor::green);
    if (fraction == 2) fraction_img.fill(Qt::GlobalColor::blue);
    if (fraction == 3) fraction_img.fill(Qt::GlobalColor::cyan);
    if (fraction == 4) fraction_img.fill(Qt::GlobalColor::yellow);
    if (fraction == 5) fraction_img.fill(Qt::GlobalColor::magenta);

    QImage nature_img;
    if (nature == 0) nature_img.load("../res/nature_0.png");
    if (nature == 1) nature_img.load("../res/nature_1.png");
    if (nature == 2) nature_img.load("../res/nature_2.png");
    if (nature == 3) nature_img.load("../res/nature_3.png");
    if (nature == 4) nature_img.load("../res/nature_4.png");
    if (nature == 5) nature_img.load("../res/nature_5.png");

    QPainter painter(&fraction_img);
    painter.drawImage(0, 0, sky_img);
    painter.end();

    if (fraction != 6) {
        painter.begin(&fraction_img);
        painter.drawImage(0, 0, nature_img);
        painter.end();
    }
    picture.convertFromImage(fraction_img);
    if (fraction == 6) picture.load("../res/generator.png");
    return picture;
}

void World::generateName()
{
    int slogi = rand()%3 + rand()%3;
    QVector<QString> begins { "О", "Па", "Ви", "Че", "Гун", "Йа", "Дта", "Ке", "Ре", "Ми", "Си", "Гли", "Рта", "Го", "Ис", "Те", "Лла", "Ге", "Йу", "Йур", "Думб", "Ул", "Лу", "Га", "Та", "На" };
    QVector<QString> slogs { "ра", "бет", "нал", "иг", "ли", "бда", "мен", "ис", "и", "о", "до", "кри", "сте", "васс", "гли", "ред", "алд", "ре", "у", "са","ка", "не", "сий", "зеп", "му" };
    name = begins[rand()%begins.size()];
    for(int i = 1; i < slogi; i++){
        name += slogs[rand()%slogs.size()];
    }
}

QString World::generateDescription()
{
    QString tsize, tfraction, tnature, turbanisation;
    description = "";
    if (size < 8) tsize = " небольшого размера";
    if (size > 18) tsize = " достаточно крупного размера";
    switch (fraction) {
        case 0 : tfraction = "красный"; break;
        case 1 : tfraction = "зеленый"; break;
        case 2 : tfraction = "синий"; break;
        case 3 : tfraction = "циановый"; break;
        case 4 : tfraction = "желтый"; break;
        case 5 : tfraction = "лиловый"; break;
    }
    switch (nature) {
        case 0 : tnature = "отсутствует"; break;
        case 1 : tnature = "убога"; break;
        case 2 : tnature = "суровая"; break;
        case 3 : tnature = "умеренная"; break;
        case 4 : tnature = "доминирует"; break;
        case 5 : tnature = "богата и щедра"; break;
    }
    switch (urbanisation) {
        case 0 : turbanisation = "ее следы не видны"; break;
        case 1 : turbanisation = "можно предположить ее наличие"; break;
        case 2 : turbanisation = "иногда встречаются ее следы"; break;
        case 3 : turbanisation = "ее наличие заметно"; break;
        case 4 : turbanisation = "ее присутствие очевидно"; break;
        case 5 : turbanisation = "она буквально перед вами"; break;
    }
    return "В окне генератора вы видите " + name + " - мир" + tsize + ", в котором преобладает "
            + tfraction + " цвет. Природа в нем " + tnature + ". Что касается разумной жизни, то " + turbanisation + ".";
}

void World::catchedItemCreatedSig(Item * item)
{
    emit sigItemCreated_from_world(item);
}

void World::catchedIsInStockSig(Resource * res)
{
    emit sigIsInStock_from_world(res);
}

void World::catchedUnitMetSig(Unit * u)
{
    emit sigUnitMet_from_world(u);
}
