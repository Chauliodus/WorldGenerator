#include "Model/Landmark/realty.h"
#include "Model/worldlevel.h"
#include "Model/world.h"

Realty::Realty(WorldLevel * parent) : Landmark(parent)
{
    // nature 0 - нет растительности
    // nature 1 - мхи, лишайники, грибы
    // nature 2 - трава
    // nature 3 - кустарник
    // nature 4 - низкие деревья
    // nature 5 - изобилие природы
    type = LndmType::REALTY;
    //resource = static_cast<Resources>(rand()%static_cast<int>(Resources::max_res));
    //loadPicture();
    //generateName();
    //generateDescription();
    isSeenFromAfar = 0;
    isAddedOnMap = 0;
    isCanBeAddedOnMap = 1;
    //если роща - то по составу деревьев
    //для деревьев - по высоте.
    //кусты - могут быть видимы, если природа 1-2.
    //пастбища - по площади и от количества высоких ландмарок на уровне.
    //           если соседние ландмарки - не леса, то почему полю не быть видимым издалека.
    QString picture_name;
    int sType = rand()%4;
    switch(sType){
        case 0 : {
            sourceType = SourceType::TREE;
            name = "Дерево";
            int res_count = rand()%2 + 1;
            resources.insert("Бревно", new Resource("Бревно", "Топор", res_count)); // этот ресурс собирается за 1 раз
            int res_2_count = rand()%5 + 1;
            resources.insert("Яблоко", new Resource("Яблоко", "NULL", res_2_count));
            description = "Это дерево, растет корнями вниз.\n\nДля рубки дерев нужен топор.";
            picture_name = "tree";
            if (parent->world_parent->nature < 5) isSeenFromAfar = 1;
            break;
        }
        case 1 : {
            sourceType = SourceType::BUSH;
            name = "Куст";
            int res_count = rand()%5 + 1;
            resources.insert("Роза", new Resource("Роза", "NULL", res_count));
            description = "Розовый куст.";
            picture_name = "flowering_bush";
            if (parent->world_parent->nature < 4) isSeenFromAfar = 1;
            break;
        }
        case 2 : {
            sourceType = SourceType::MEADOW;
            name = "Луг";
            resources.insert("Трава", new Resource("Трава", "NULL", 10000));
            description = "Это поле, поросшее разнотравьем.";
            picture_name = "meadow";
            bool landscape_pass = (parent->landscape == Landscapes::PLAIN) ||
                    (parent->landscape == Landscapes::LOWLAND) ||
                    (parent->landscape == Landscapes::PLATEAU) ||
                    (parent->landscape == Landscapes::ICE_WASTELAND);
            if (landscape_pass) isSeenFromAfar = 1;
            break;
        }
        case 3 : {
            sourceType = SourceType::MINE;
            name = "Шахта";
            int res_count = rand()%15 + 10;
            resources.insert("Руда", new Resource("Руда", "Кирка", res_count));
            description = "Вход в подземелье, похожее на какую-то шахту.\n\nДля добычи руд нужна кирка.";
            picture_name = "mine";
            bool landscape_pass = (parent->landscape == Landscapes::PLAIN) ||
                    (parent->landscape == Landscapes::LOWLAND) ||
                    (parent->landscape == Landscapes::PLATEAU) ||
                    (parent->landscape == Landscapes::ICE_WASTELAND);
            landscape_pass = landscape_pass && (parent->world_parent->nature == 0);
            if (landscape_pass) isSeenFromAfar = 1; // если не долина и не скрыт во мхах, то виден издалека.
        }
    }

    picture.load("../res/realties/" + picture_name + ".png");
    picture_preview.load("../res/realties/" + picture_name + "_preview.png");
    picture_preview_hovered.load("../res/realties/" + picture_name + "_preview_hovered.png");
}
void Realty::generateName()
{
    int a = rand()%3;
    switch (a) {
        case 0 : name = "Луг"; break;
        case 1 : name = "Роща"; break;
        case 2 : name = "Грибница"; break;
    }
}
void Realty::generateDescription()
{
    description = "Это нечто среднее между лугом, рощей и болотом.";
}

void Realty::loadPicture()
{
    picture.load("../res/realties/meadow.png");
    picture_preview.load("../res/realties/meadow_preview.png");
    picture_preview_hovered.load("../res/realties/meadow_preview_hovered.png");
}
void Realty::research()
{
    if (sourceType == SourceType::TREE){ qDebug() << "Это дерево, вероятно, деревянное."; }
}
void Realty::get()
{
    if (sourceType == SourceType::BUSH){
        Item * item = new Item;
        // ресурс.название, ресурс.количество, ресурс.картинки?
        item->name = "Роза";
        item->count = resources["Роза"]->count;
        item->picture_name = "rose";
        item->picture.load("../res/items/" + item->picture_name + ".png");
        item->picture_preview.load("../res/items/" + item->picture_name + "_preview.png");
        item->picture_preview_hovered.load("../res/items/" + item->picture_name + "_preview_hovered.png");
        item->parent = this;
        // ландмарка меняет состояние: уменьшается ресурс, меняется картинка и превью
        resources["Роза"]->count -= item->count;
        //this->count = 0; // ресурс собран
        this->picture_name = "bush";
        this->picture.load("../res/realties/" + this->picture_name + ".png");
        this->picture_preview.load("../res/realties/" + this->picture_name + "_preview.png");
        this->picture_preview_hovered.load("../res/realties/" + this->picture_name + "_preview_hovered.png");
        //this->get_string = "NULL";
        this->description = "Сейчас на кусте нет цветов, но позже они вырастут.";
        emit sigItemAddingToInventory(item);
    }
    if (sourceType == SourceType::MINE){
        Item * item = new Item;
        // ресурс.название, ресурс.количество, ресурс.картинки?
        item->name = "Руда";
        item->count = rand()%2 + 1;
        qDebug() << "Mine contains" << max_resource << ", hero gain" << item->count;
        if (item->count > resources["Руда"]->count){
            do { item->count = rand()%2 + 1;
            qDebug() << "Mine is nearby to be empty:" << resources["Руда"]->count;
            qDebug() << "Trying to get:" << item->count;
            } while (item->count > resources["Руда"]->count);
        }
        resources["Руда"]->count -= item->count;
        qDebug() << "Now mine contains" << resources["Руда"]->count;
        item->picture_name = "ore";
        item->picture.load("../res/items/" + item->picture_name + ".png");
        item->picture_preview.load("../res/items/" + item->picture_name + "_preview.png");
        item->picture_preview_hovered.load("../res/items/" + item->picture_name + "_preview_hovered.png");
        item->parent = this;
        // ландмарка меняет состояние: уменьшается ресурс, меняется картинка и превью
        if (resources["Руда"]->count <= 0) {
            qDebug() << "Mine is empty.";
            //this->get_string = "NULL"; // ресурс собран
            this->description = "Шахта выработана. Больше ресурсов в ней нет.";
        }
        emit sigItemAddingToInventory(item);
    }
    if (sourceType == SourceType::TREE){
        Item * item = new Item;
        // ресурс.название, ресурс.количество, ресурс.картинки?
        item->name = "Бревно";
        item->count = resources["Бревно"]->count;
        item->picture_name = "log";
        item->picture.load("../res/items/" + item->picture_name + ".png");
        item->picture_preview.load("../res/items/" + item->picture_name + "_preview.png");
        item->picture_preview_hovered.load("../res/items/" + item->picture_name + "_preview_hovered.png");
        item->parent = this;
        // ландмарка меняет состояние: уменьшается ресурс, меняется картинка и превью
        resources["Бревно"]->count -= item->count;; // ресурс собран
        resources["Яблоко"]->count = 0; // яблочки пропали при срубании
        this->picture_name = "stump";
        this->picture.load("../res/realties/" + this->picture_name + ".png");
        this->picture_preview.load("../res/realties/" + this->picture_name + "_preview.png");
        this->picture_preview_hovered.load("../res/realties/" + this->picture_name + "_preview_hovered.png");
        //this->get_string = "NULL";
        this->description = "Пень от срубленного дерева.";
        emit sigItemAddingToInventory(item);
    }
    if (sourceType == SourceType::MEADOW){
        /* сделать много картинок с травами, из которых большинство сорняки и показываются рандомно и пока не надоест */
        Item * item = new Item;
        // ресурс.название, ресурс.количество, ресурс.картинки?
        item->name = "Трава";
        item->count = rand()%10 + 5;
        resources["Трава"]->count -= item->count;
        item->picture_name = "grass";
        item->picture.load("../res/items/" + item->picture_name + ".png");
        item->picture_preview.load("../res/items/" + item->picture_name + "_preview.png");
        item->picture_preview_hovered.load("../res/items/" + item->picture_name + "_preview_hovered.png");
        item->parent = this;
        // ландмарка меняет состояние: уменьшается ресурс, меняется картинка и превью
        resources["Трава"]->count -= item->count;; // ресурс собран
        emit sigItemAddingToInventory(item);
    }
}

void Realty::onVisit()
{
    actions.clear();
    switch (sourceType) {
        case SourceType::BUSH : {
            actions.push_back(new QPair<QString, QString>("Осмотреть", "research"));
            if (resources["Роза"]->count > 0)
                actions.push_back(new QPair<QString, QString>("Собрать цветочки", "get"));
            actions.push_back(new QPair<QString, QString>("Удобрить", "research"));
            actions.push_back(new QPair<QString, QString>("Выкопать", "research"));
            actions.push_back(new QPair<QString, QString>("Сжечь", "destroy"));
            break;
        }
        case SourceType::MINE : {
            actions.push_back(new QPair<QString, QString>("Войти", "research"));
            actions.push_back(new QPair<QString, QString>("Осмотреть", "research"));
            emit sigIsItemInStack(resources["Руда"]);
            if(resources["Руда"]->is_item_in_stack && resources["Руда"]->count > 0){
                description = "Вход в подземелье, похожее на какую-то шахту.";
                actions.push_back(new QPair<QString, QString>("Добыть руду", "get"));
            }
            actions.push_back(new QPair<QString, QString>("Сделать логовом", "research"));
            actions.push_back(new QPair<QString, QString>("Взорвать (обвалить)", "destroy"));
            break;
        }
        case SourceType::TREE : {
            actions.push_back(new QPair<QString, QString>("Осмотреть", "research"));
            emit sigIsItemInStack(resources["Бревно"]);
            qDebug() << resources["Бревно"]->count << resources["Бревно"]->is_item_in_stack;
            if (resources["Бревно"]->count > 0 && resources["Бревно"]->is_item_in_stack){
                description = "Это дерево, растет корнями вниз.";
                actions.push_back(new QPair<QString, QString>("Срубить", "get"));
            }
            if (resources["Яблоко"]->count > 0)
                actions.push_back(new QPair<QString, QString>("Собрать плоды", "research"));
            if (resources["Бревно"]->count == 0)
                actions.push_back(new QPair<QString, QString>("Выкорчевать", "research"));
            actions.push_back(new QPair<QString, QString>("Удобрить", "research"));
            actions.push_back(new QPair<QString, QString>("Сжечь", "destroy"));
            break;
        }
        case SourceType::MEADOW : {
            actions.push_back(new QPair<QString, QString>("Осмотреть", "research"));
            actions.push_back(new QPair<QString, QString>("Нарвать травы", "get"));
            actions.push_back(new QPair<QString, QString>("Удобрить", "research"));
            actions.push_back(new QPair<QString, QString>("Сжечь", "destroy"));
            actions.push_back(new QPair<QString, QString>("Засыпать солью", "destroy"));
            break;
        }
    }
}

void Realty::f1()
{
    qDebug() << "f1";
}

void Realty::f2()
{
    qDebug() << "f2";
}

void Realty::f3()
{
    qDebug() << "f3";
}

void Realty::f4()
{
    qDebug() << "f4";
}

void Realty::f5()
{
    qDebug() << "f5";
}

void Realty::f6()
{
    qDebug() << "f6";
}

void Realty::f7()
{
    qDebug() << "f7";
}

void Realty::f8()
{
    qDebug() << "f8";
}

void Realty::f9()
{
    qDebug() << "f9";
}

void Realty::f10()
{
    qDebug() << "f10";
}
void Realty::destroy()
{
    QMapIterator<QString, Resource *> i(resources);
    while (i.hasNext()) {
         i.next();
         delete i.value();
    }
}
