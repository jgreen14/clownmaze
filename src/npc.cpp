#include "..\include\npc.h"

NPC::NPC()
{
    actType = NONPLAYER;
}//NPC

NPC::NPC(NPC* source) : ShapeActor::ShapeActor((ShapeActor*)source)
{
    actType = source->actorType();
    playerHostile = source->getPlayerHostile();
    hp = source->getHP();
    speedScale = 0.01;
    unitScale = (float)1/MAXNPCSPEED;
    maxMagnitude = sqrt((MAXNPCSPEED*MAXNPCSPEED*unitScale*unitScale) + (MAXNPCSPEED*MAXNPCSPEED*unitScale*unitScale)) * speedScale;
}//NPC - copy constructor

NPC::NPC(NPC* source, float x, float y) : ShapeActor::ShapeActor((ShapeActor*)source)
{
    actType = source->actorType();
    playerHostile = source->getPlayerHostile();
    hp = source->getHP();
    this->x = x;
    this->y = y;
    speedScale = 0.01;
    unitScale = (float)1/MAXNPCSPEED;
    maxMagnitude = sqrt((MAXNPCSPEED*MAXNPCSPEED*unitScale*unitScale) + (MAXNPCSPEED*MAXNPCSPEED*unitScale*unitScale)) * speedScale;
}//NPC

NPC::NPC(float x, float y, float z, float direction, int renderWidth) : ShapeActor::ShapeActor(x, y, z, direction, renderWidth)
{
    actType = NONPLAYER;
    playerHostile = false;
    speedScale = 0.01;
    unitScale = (float)1/MAXNPCSPEED;
    maxMagnitude = sqrt((MAXNPCSPEED*MAXNPCSPEED*unitScale*unitScale) + (MAXNPCSPEED*MAXNPCSPEED*unitScale*unitScale)) * speedScale;
}//NPC

NPC::~NPC()
{
    //dtor
}//~NPC

void NPC::update(int inputVal, Map* map, sf::Time elapsed, float rotation)
{
    ySpeed = MAXNPCSPEED;

    shapeHit = -1;
    if (flashCounter > 0)
        flashCounter -= 1;
    else
        shape->setFillColor(sf::Color(255,255,255));

    this->direction = fmodf(getAnglePlayer()+PI, CIRCLE);
    move(FORWARD, map, 1);
}//update

bool NPC::getPlayerHostile()
{
    return playerHostile;
}//getPlayerHostile

void NPC::setPlayerHostile(bool hostile)
{
    playerHostile = hostile;
}//setPlayerHostile
