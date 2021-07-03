#include "game.h"

Game::Game(QObject *parent) : QObject(parent)
{
    srand(time(nullptr));
    hero = new Hero();
    generator = new World(true);
    curloc = new Location;
    new_world = nullptr;
}

void Game::createWorld()
// создается новый мир. Вид из окна генератора. Только статы.
// при посещении мир добавляется в местоположение, генерятся уровни и ландмарки.
{
    if (new_world != nullptr) delete new_world;
    new_world = new World;
    emit sigWorldCreated();
}

void Game::researchWorld()
{
    curloc->world = new_world;
    connect(curloc->world, &World::sigItemCreated_from_world, this, &Game::addItemToInventory);
    connect(curloc->world, &World::sigIsInStock_from_world, this, &Game::isItemInStock);
    connect(curloc->world, &World::sigUnitMet_from_world, this, &Game::unitMet);
    curloc->level_num = 0;
    curloc->level = curloc->world->level_list[curloc->level_num];
    curloc->lndm = nullptr;
    curloc->landmark_num = NULL;
    emit sigWorldChanged();
}

void Game::researchLevel()
{
    int num = rand()%curloc->level->size;
    curloc->landmark_num = num;
    curloc->lndm = curloc->level->landmark_list[num];
    emit sigLandmarkChanged(curloc->lndm);
}

void Game::increaseLvl()
{
    if (curloc->level_num < curloc->world->size - 1){
        curloc->lndm = nullptr;
        curloc->landmark_num = NULL;
        curloc->level_num++;
        curloc->level = curloc->world->level_list[curloc->level_num];
        emit sigLevelChanged();
    }
}

void Game::decreaseLvl()
{
    curloc->lndm = nullptr;
    curloc->landmark_num = NULL;
    if (curloc->level_num == 0){
        new_world = curloc->world;
        curloc->world = generator;
        emit sigWorldChanged();
        return;
    }
    if (curloc->level_num > 0){
        curloc->level_num--;
        curloc->level = curloc->world->level_list[curloc->level_num];
        emit sigLevelChanged();
    }
}

void Game::selectLandmark(Landmark * l)
{
    curloc->lndm = l;
    curloc->landmark_num = l->number;
    emit sigLandmarkChanged(curloc->lndm);
}

void Game::addOnMap()
{
    curloc->lndm->isAddedOnMap = true;
    emit sigLandmarkAddedOnMap();
}

void Game::addItemToInventory(Item *new_item)
{
    // проверка: есть уже в инвентаре такая вещь? Если да, то количество увеличивается.
    bool added = false;
    if (hero->inventory.size() > 0) {
        std::for_each(hero->inventory.begin(), hero->inventory.end(), [new_item, &added, this](Item * item){
            if(item->name == new_item->name){
                qDebug() << item->count << new_item->count;
                int count_old = new_item->count;
                item->count += new_item->count;
                item->tooltip = item->name + " " + QString::number(item->count) + " шт.";
                added = true;
                emit sigSendMessageToView("Вы помещаете в инвентарь " + QString::number(count_old) + " " + new_item->name);
                return; // ВЫХОД ИЗ ЛЯМБДЫ, А НЕ ВСЕЙ ФУНКЦИИ!
            }
        });
    }
    new_item->isInInventory = true;
    new_item->tooltip = new_item->name + " " + QString::number(new_item->count) + " шт.";
    if (!added) hero->inventory.push_back(new_item);
    // перерисовываем ландмарку. Если вещь подобрана с земли, т.е. родителя нет, то лндм покидается, вьюха рисует уровень.
    emit sigLandmarkChanged(new_item->parent);
    emit sigSendMessageToView("Вы помещаете в инвентарь " + QString::number(new_item->count) + " " + new_item->name);
}

void Game::isItemInStock(Resource * res)
{
    if (hero->inventory.size() > 0){
        std::for_each(hero->inventory.begin(), hero->inventory.end(), [this, res](Item * item){
            if(item->name == res->required_item) res->is_item_in_stack = true;
        });
    }

}

void Game::unitMet(Unit * unit)
{
    meetings.push_back(new Meeting(hero, unit, this));
}
