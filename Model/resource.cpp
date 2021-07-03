#include "resource.h"

Resource::Resource(QObject *parent) : QObject(parent)
{

}

Resource::Resource(QString name, QString req_item, int count)
    : name(name), required_item(req_item), count(count)
{
    is_item_in_stack = false;
}
