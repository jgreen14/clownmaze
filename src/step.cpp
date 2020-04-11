#include "../include/step.h"

Step::Step()
{
    x = 0;
    y = 0;
    length2 = 0;
    offset = 0;
    height = 0;
    distance = 0;
    shading = 0;
}//Step()

Step::Step(float x, float y)
{
    this->x = x;
    this->y = y;
    length2 = 0;
    offset = 0;
    height = 0;
    distance = 0;
    shading = 0;
}//Step(float, float)

Step::~Step()
{
    //dtor
}

float Step::getX()
{
    return x;
}//getX

float Step::getY()
{
    return y;
}//getY

float Step::getLength2()
{
    return length2;
}//getLength2

float Step::getOffset()
{
    return offset;
}//getOffset

float Step::getHeight()
{
    return height;
}//getHeight

float Step::getDistance()
{
    return distance;
}//getDistance

float Step::getShading()
{
    return shading;
}//getShading

void Step::copy(Step* copyStep)
{
    copyStep->setX(x);
    copyStep->setY(y);
    copyStep->setLength2(length2);
    copyStep->setOffset(offset);
    copyStep->setHeight(height);
    copyStep->setDistance(distance);
    copyStep->setShading(shading);
}//copy

void Step::setX(float x)
{
    this->x = x;
}//setX

void Step::setY(float y)
{
    this->y = y;
}//setY

void Step::setLength2(float length)
{
    length2 = length;
}//setLength2

void Step::setOffset(float offset)
{
    this->offset = offset;
}//setOffset

void Step::setHeight(float height)
{
    this->height = height;
}//setHeight

void Step::setDistance(float distance)
{
    this->distance = distance;
}//setDistance

void Step::setShading(float shading)
{
    this->shading = shading;
}//setShading
