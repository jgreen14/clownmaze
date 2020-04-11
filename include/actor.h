#ifndef ACTOR_H
#define ACTOR_H

#include <SFML/System.hpp>
#include <math.h>
#include "../include/enum.h"

class Map;

class Actor
{
    public:
        Actor();
        Actor(Actor*);
        Actor(float, float, float, float);
        virtual ~Actor();
        float getX();
        float getY();
        float getZ();
        float getDirection();
        int getHP();
        void setHP(int);
        virtual void takeDamage(int);
        int getFriction();
        void setFriction(int);
        float getXSpeed();
        float getYSpeed();
        bool isActive();
        void deactivate();
        virtual void update(int, Map*, sf::Time, float) =0;
        virtual ACTORTYPE actorType();
    protected:
        float x;
        float y;
        float z;
        float direction; //Direction player is facing in RADIANS
        int xSpeed;
        int ySpeed;
        float speedScale;
        float unitScale;
        float maxMagnitude;
        int hp;
        ACTORTYPE actType;
        int friction;
        bool active;

        void move(int, Map*, float);
        void rotate(float);
    private:
};

#endif // ACTOR_H
