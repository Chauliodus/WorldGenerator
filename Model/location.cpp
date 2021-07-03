#include "location.h"

Location::Location(QObject *parent) : QObject(parent)
{
    world = nullptr;
    world_num = NULL;
    level = nullptr;
    level_num = NULL;
    lndm = nullptr;
    landmark_num = NULL;
}
