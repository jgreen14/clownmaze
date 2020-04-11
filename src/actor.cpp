#include "../include/actor.h"
#include "../include/map.h"

Actor::Actor()
{
    x = 0;
    y = 0;
    z = 0;
    direction = 0;
    xSpeed = 0;
    ySpeed = 0;
    speedScale = 1;
    unitScale = 1;
    maxMagnitude = 1;
    hp = 100;
    friction = 0;
    active = true;
}//Actor

Actor::Actor(Actor* source)
{
    x = source->getX();
    y = source->getY();
    z = source->getZ();
    direction = source->getDirection();
    hp = source->getHP();
    friction = source->getFriction();
    active = true;
    xSpeed = 0;
    ySpeed = 0;
    speedScale = 1;
    unitScale = 1;
    maxMagnitude = 1;
}//Actor - copy constructor

Actor::Actor(float x, float y, float z, float direction)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->direction = direction;
    xSpeed = 0;
    ySpeed = 0;
    speedScale = 1;
    unitScale = 1;
    maxMagnitude = 1;
    hp = 100;
    friction = 0;
    active = true;
}//Actor

Actor::~Actor()
{
    //dtor
}//~Actor

float Actor::getX()
{
    return x;
}//getX

float Actor::getY()
{
    return y;
}//getY

float Actor::getZ()
{
    return z;
}//getZ

float Actor::getDirection()
{
    return direction;
}//getDirection

void Actor::move(int dir, Map* map, float timeFactor)
{
    float dx = 0;
    float dy = 0;
    float maxDx = 0;
    float maxDy = 0;
    float realXSpeed = xSpeed*unitScale*timeFactor;
    float realYSpeed = ySpeed*unitScale*timeFactor;
    float moveDir = atan2(realXSpeed, realYSpeed);
    float magnitude;
    float buffer = 3; //Buffer so we can't walk too close to a wall
    int floorZ = floor(this->z);
    bool hitWall = false;

    if (moveDir < 0)
        moveDir = PI + PI - (-1 * moveDir);

    realXSpeed = sin(moveDir) * realXSpeed;
    realYSpeed = cos(moveDir) * realYSpeed;

    moveDir = fmodf(moveDir + direction + CIRCLE, CIRCLE);
    magnitude = sqrt((realXSpeed*realXSpeed) + (realYSpeed*realYSpeed)) * speedScale;

    dx = cos(moveDir) * magnitude;
    maxDx = cos(moveDir) * maxMagnitude;
    dy = sin(moveDir) * magnitude;
    maxDy = sin(moveDir) * maxMagnitude;

    if (map->get(this->x + maxDx * buffer, this->y) <= floorZ)
        x += dx;
    else
        hitWall = true;

    if (map->get(this->x, this->y + maxDy * buffer) <= floorZ)
        y += dy;
    else
        hitWall = true;

    if (hitWall && this->actType == BULLET)
        this->active = false;
    //std::cout << dx << " " << dy << " " << magnitude << " " << xSpeed << " " << ySpeed << std::endl;
}//move

void Actor::rotate(float angle)
{
    direction = fmodf((direction + angle + CIRCLE), CIRCLE);
}//rotate

int Actor::getHP()
{
    return hp;
}//getHP

void Actor::setHP(int hp)
{
    this->hp = hp;
}//setHP

void Actor::takeDamage(int damage)
{
    hp -= damage;
    if (hp <= 0)
        this->deactivate();
}//takeDamage

ACTORTYPE Actor::actorType()
{
    return actType;
}//actorType

int Actor::getFriction()
{
    return friction;
}//getFriction

void Actor::setFriction(int friction)
{
    this->friction = friction;
}//setFriction

float Actor::getXSpeed()
{
    return xSpeed;
}//getXSpeed

float Actor::getYSpeed()
{
    return ySpeed;
}//getYSpeed

bool Actor::isActive()
{
    return active;
}//isActive

void Actor::deactivate()
{
    this->active = false;
}//deactivate
