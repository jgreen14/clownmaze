#include "../include/player.h"
#include "../include/map.h"

Player::Player()
{
    actType = PLAYER;
}//Player

Player::Player(float x, float y, float z, float direction) : Actor::Actor(x, y, z, direction)
{
    paces = 0;
    speedScale = 0.05;
    friction = 10;
    unitScale = (float)1/MAXPLAYERSPEED;
    maxMagnitude = sqrt((MAXPLAYERSPEED*MAXPLAYERSPEED*unitScale*unitScale) + (MAXPLAYERSPEED*MAXPLAYERSPEED*unitScale*unitScale)) * speedScale;
    actType = PLAYER;
}//Player(float, float, float)

Player::~Player()
{
    //dtor
}//~Player

void Player::update(int dir, Map* map, sf::Time elapsed, float rotation)
{
    float timeFactor = elapsed.asMilliseconds()/FRAMELENGTH;

    if (xSpeed > 0)
        xSpeed -= friction;
    else if (xSpeed < 0)
        xSpeed += friction;

    if (ySpeed > 0)
        ySpeed -= friction;
    else if (ySpeed < 0)
        ySpeed += friction;

    if (dir & MOUSETURN)
        rotate(rotation * timeFactor);
    if (dir & LEFT)
        rotate(-0.025 * timeFactor);
    if (dir & RIGHT)
        rotate(0.025 * timeFactor);
    if (dir & FORWARD)
        if (ySpeed < MAXPLAYERSPEED)
            ySpeed += PLAYERACCEL + friction;
    if (dir & BACKWARD)
        if (ySpeed > -1 * MAXPLAYERSPEED)
            ySpeed -= PLAYERACCEL + friction;
    if (dir & STRAFERIGHT)
        if (xSpeed < MAXPLAYERSPEED)
            xSpeed += PLAYERACCEL + friction;
    if (dir & STRAFELEFT)
        if (xSpeed > -1 * MAXPLAYERSPEED)
            xSpeed -= PLAYERACCEL + friction;
    if (dir & UP || dir & DOWN)
        fly(dir, map, timeFactor);

    move(dir, map, timeFactor);
}//update

void Player::fly(int dir, Map* map, float timeFactor)
{
    float dz = 0.1 * timeFactor;
    float newZ = 0;

    if (dir & DOWN)
        dz *= -1;
    newZ = this->z + dz;

    if (dir & UP)
    {
        if (newZ <= (map->getMaxHeight() - 0.99))
            z = newZ;
    }//if
    if (dir & DOWN)
    {
        if (newZ >= map->get(this->x, this->y))
            z = newZ;
    }//if
}//fly
