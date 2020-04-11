#include "..\include\bullet.h"

Bullet::Bullet()
{
    actType = BULLET;
}//BULLET

Bullet::Bullet(float x, float y, float z, float direction, float xSpeed, float ySpeed, int renderWidth) : ShapeActor::ShapeActor(x, y, z, direction, renderWidth)
{
    actType = BULLET;
    //this->xSpeed = xSpeed;
    this->ySpeed = ySpeed;
    speedScale = 0.1;
    unitScale = (float)1/MAXBULLETSPEED;
    maxMagnitude = sqrt((MAXBULLETSPEED*MAXBULLETSPEED*unitScale*unitScale) + (MAXBULLETSPEED*MAXBULLETSPEED*unitScale*unitScale)) * speedScale;
    damage = 10;
}//NPC

Bullet::~Bullet()
{
    //dtor
}

void Bullet::update(int inputVal, Map* map, sf::Time elapsed, float rotation)
{
    shapeHit = -1;
    //ySpeed = 2;
    if (xSpeed < 0)
        xSpeed += 10;
    else if (xSpeed > 0)
        xSpeed -= 10;

    if (ySpeed < MAXBULLETSPEED)
        ySpeed += BULLETACCEL;
    move(FORWARD, map, 1);
}//update

int Bullet::getDamage()
{
    return damage;
}//getDamage
