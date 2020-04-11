#ifndef PLAYER_H
#define PLAYER_H

#define MAXPLAYERSPEED 100
#define PLAYERACCEL 20

#include <iostream>
#include <string>
#include <math.h>
#include "../include/actor.h"

class Map;

class Player : public Actor
{
    public:
        Player();
        Player(float, float, float, float);
        virtual ~Player();
        void update(int, Map*, sf::Time, float rotation=0);
    protected:
    private:
        void fly(int, Map*, float);
        float paces; //Number of steps taken by player (for animation)
};

#endif // PLAYER_H
