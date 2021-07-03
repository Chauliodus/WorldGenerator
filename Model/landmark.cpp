#include "Model/landmark.h"
#include "Model/Landmark/item.h"
#include <Model/Landmark/unit.h>
#include "worldlevel.h"
#include "useraction.h"
#include <QDebug>

Landmark::Landmark(Landmark * source)
{
    wlevel_parent = source->wlevel_parent;
    type = source->type;
    name = source->name;
    description = source->description;
    picture_name = source->picture_name;
    picture = source->picture;
    picture_preview = source->picture_preview;
    picture_preview_hovered = source->picture_preview_hovered;
    actions = source->actions;

    //owner = source->owner;
    isSeenFromAfar = source->isSeenFromAfar;
    isAddedOnMap = source->isAddedOnMap;
    isCanBeAddedOnMap = source->isCanBeAddedOnMap;

    steals = source->steals;
}

Landmark::Landmark(WorldLevel * parent) : wlevel_parent(parent)
{

}
void Landmark::research()
{

}
void Landmark::get()
{

}
void Landmark::destroy()
{

}
