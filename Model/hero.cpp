#include "Model/hero.h"

Hero::Hero(QObject *parent) : QObject(parent)
{
    willpower = rand()%5;
    logic = rand()%5;
    physic = rand()%5;
    ethic = rand()%5;
    meeting = nullptr;
    stealth = physic;
    attention = logic;
    domination = willpower;
}
