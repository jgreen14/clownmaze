#include "../include/item.h"

Item::Item()
{

}//Item()

Item::Item(Item* source, float x, float y) : ShapeActor::ShapeActor((ShapeActor*)source)
{
    value = source->getValue();
    type = source->getType();
    actType = source->actorType();
    this->x = x;
    this->y = y;
}//Item

Item::Item(Item* source) : ShapeActor::ShapeActor((ShapeActor*)source)
{
    actType = source->actorType();
    value = source->getValue();
    type = source->getType();
}//Item - copy constructor

Item::Item(float x, float y, float z, float direction, int renderWidth) : ShapeActor::ShapeActor(x, y, z, direction, renderWidth)
{
    actType = ITEM;
    value = 0;
    type = UNKNOWN;
    //updatePlayerVals();
}//Item

Item::~Item()
{
    //dtor
}//~Item

void Item::update(int inputVal, Map* map, sf::Time elapsed, float rotation)
{
    //updatePlayerVals();
    shapeHit = -1;
}//update

int Item::getValue()
{
    return value;
}//getValue

void Item::setValue(int value)
{
    this->value = value;
}//setValue

ITEMTYPE Item::getType()
{
    return type;
}//getType

void Item::setType(ITEMTYPE type)
{
    this->type = type;
}//setType
