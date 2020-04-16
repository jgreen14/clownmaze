#include "../include/shapeactor.h"

ShapeActor::ShapeActor()
{

}//ShapeActor

ShapeActor::ShapeActor(ShapeActor* source) : Actor::Actor((Actor*)source)
{
    shape = new sf::RectangleShape();
    shapeHit = source->getHit();
    shapeScale = source->getScale();
    distancePlayer = source->getDistancePlayer();
    anglePlayer = source->getAnglePlayer();
    shapeWidth = source->getShapeWidth();
    rightColumn = source->getRightCol();
    leftColumn = source->getLeftCol();
    imageIndex = source->getImageIndex();
    flashCounter = 0;
}//ShapeActor - copy constructor

ShapeActor::ShapeActor(float x, float y, float z, float direction, int renderWidth) : Actor::Actor(x, y, z, direction)
{
    shape = new sf::RectangleShape();
    shapeHit = -1;
    distancePlayer = 0;
    anglePlayer = 0;
    shapeWidth = 0;
    rightColumn = -1;
    leftColumn = -1;
    imageIndex = -1;
    shapeScale = (float)renderWidth/1024.0;
    flashCounter = 0;
}//ShapeActor

ShapeActor::~ShapeActor()
{
    delete shape;
}//~ShapeActor

sf::RectangleShape* ShapeActor::getShape()
{
    return shape;
}//shape

float ShapeActor::getAnglePlayer()
{
    if (anglePlayer >= 0)
    {
        return anglePlayer;
    }//if
    else
    {
        return PI + PI - (-1 * anglePlayer);
    }//else
}//getAnglePlayer

void ShapeActor::setAnglePlayer(float playerX, float playerY)
{
    anglePlayer = atan2(y - playerY, x - playerX);
}//setAnglePlayer

float ShapeActor::getDistancePlayer()
{
    return distancePlayer;
}//getDistance

void ShapeActor::setDistancePlayer(float playerX, float playerY)
{
    distancePlayer = sqrt((x - playerX) * (x - playerX) + (y - playerY) * (y - playerY));
}//setDistancePlayer

void ShapeActor::updateShapeWidth()
{
    shapeWidth = shape->getTexture()->getSize().x / distancePlayer * shapeScale;
}//updateShapeWidth

float ShapeActor::getShapeWidth()
{
    return shapeWidth;
}//getShapeWidth

int ShapeActor::getHit()
{
    return shapeHit;
}//getHit

void ShapeActor::setHit(int hit)
{
    shapeHit = hit;
}//setHit

float ShapeActor::getWidth()
{
    return shapeWidth;
}//getWidth

int ShapeActor::getRightCol()
{
    return rightColumn;
}//getRightCol

void ShapeActor::setRightCol(int column)
{
    rightColumn = column;
}//setRightCol

int ShapeActor::getLeftCol()
{
    return leftColumn;
}//getLeftCol

void ShapeActor::setLeftCol(int column)
{
    leftColumn = column;
}//setLeftCol

float ShapeActor::getScale()
{
    return shapeScale;
}//getScale

int ShapeActor::getImageIndex()
{
    return imageIndex;
} // getImageIndex

void ShapeActor::setImageIndex(int imageIndex)
{
    this->imageIndex = imageIndex;
} // setImageIndex

void ShapeActor::takeDamage(int damage)// : Actor::takeDamage(damage)
{
    hp -= damage;
    if (hp <= 0)
        this->deactivate();
    else
    {
        if (this->actType == NONPLAYER)
        {
            //shape->setFillColor(sf::Color(192,0,0));
            flashCounter = FLASHTIME;
        }//if
    }//else
}//takeDamage

bool ShapeActor::flashing()
{
    if (flashCounter > 0)
        return true;
    else
        return false;
}//flashing
