#include "Model/Landmark/unit.h"
#include "Model/worldlevel.h"
#include "Model/world.h"

Unit::Unit(WorldLevel * parent) : Landmark(parent), parent(parent)
{
    createRandomUnit();
}

Unit::Unit(Unit * source)
{
    willpower = source->willpower;
    logic = source->logic;
    physic = source->physic;
    ethic = source->ethic;
    inventory = source->inventory;
    cameraden = source->cameraden;
    marks = source->marks;
    meeting = source->meeting;
    stealth = source->stealth;
    attention = source->stealth;
    domination = source->domination;
    suffering = source->suffering;
    pride = source->pride;
}
void Unit::generateName()
{
    int a = rand()%3;
    switch (a) {
        case 0 : name = "Животное"; break;
        case 1 : name = "Человек"; break;
        case 2 : name = "Призрак"; break;
    }
}
void Unit::generateDescription()
{
    description = "Нам ведь все равно, кого убивать, правда?";
}

void Unit::loadPicture()
{
    picture.load("../res/units/man.png");
    picture_preview.load("../res/units/man_preview.png");
    picture_preview_hovered.load("../res/units/man_preview_hovered.png");
}

void Unit::createRandomUnit()
{
    meeting = nullptr;
    type = LndmType::UNIT;
    loadPicture();
    generateName();
    generateDescription();
    isSeenFromAfar = 0;
    isAddedOnMap = 0;
    isCanBeAddedOnMap = 0;

    physic = rand()%5;
    logic = rand()%5;
    ethic = rand()%5;
    willpower = rand()%5;

    stealth = rand()%5;
    attention = rand()%5;
    domination = rand()%5;
    suffering = rand()%5;
    pride = rand()%5;
    /*
    if(parent->number <= 5) {
        physic = parent->number;
        logic = rand()%parent->number;
        ethic = rand()%parent->number;
        willpower = rand()%parent->number;
    }
    if(parent->number > 5 && parent->number <= 10) {
        if (parent->world_parent->color == Fractions::RED) { // bonus to WILL
            physic = rand()%(parent->number * 2) + 5;
            logic = rand()%(parent->number * 2) + 5;
            ethic = rand()%(parent->number * 2) + 5;
            willpower = rand()%(parent->number * 2 + 5) + 5;
        }
        if (parent->world_parent->color == Fractions::GREEN) { // bonus to PHYS
            physic = rand()%(parent->number * 2 + 5) + 5;
            logic = rand()%(parent->number * 2) + 5;
            ethic = rand()%(parent->number * 2) + 5;
            willpower = rand()%(parent->number * 2) + 5;
        }
        if (parent->world_parent->color == Fractions::BLUE) { // bonus to LOG
            physic = rand()%(parent->number * 2) + 5;
            logic = rand()%(parent->number * 2 + 5) + 5;
            ethic = rand()%(parent->number * 2) + 5;
            willpower = rand()%(parent->number * 2) + 5;
        }
        if (parent->world_parent->color == Fractions::CYAN) { // bonus to LOG and PHYS, debuff to WILL
            physic = rand()%(parent->number * 2 + 5) + 5;
            logic = rand()%(parent->number * 2 + 5) + 5;
            ethic = rand()%(parent->number * 2) + 5;
            willpower = rand()%(parent->number * 2 - 5) + 5;
        }
        if (parent->world_parent->color == Fractions::YELLOW) { // bonus to ETH
            physic = rand()%(parent->number * 2) + 5;
            logic = rand()%(parent->number * 2) + 5;
            ethic = rand()%(parent->number * 2 + 5) + 5;
            willpower = rand()%(parent->number * 2) + 5;
        }
        if (parent->world_parent->color == Fractions::MAGENTA) { // bonus to ETH and LOG, debuff to PHYS
            physic = rand()%(parent->number * 2 - 5) + 5;
            logic = rand()%(parent->number * 2 + 5) + 5;
            ethic = rand()%(parent->number * 2 + 5) + 5;
            willpower = rand()%(parent->number * 2) + 5;
        }
    }
    // if (parent->world_parent > 10) { }
    stealth = rand()%physic;
    attention = rand()%logic;
    domination = rand()%willpower;
    suffering = 0;
    pride = rand()%willpower;*/
}
void Unit::research()
{
    qDebug() << "Вы разговариваете с человеком.";
}
void Unit::get()
{
    qDebug() << "Get" << name << " " << description;
}

void Unit::onVisit()
{
    actions.clear();
    emit sigUnitMet(this);
    //createRandomUnit();
}

void Unit::sayHello()
{

}
void Unit::destroy()
{

}
