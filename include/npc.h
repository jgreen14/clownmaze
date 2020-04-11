#ifndef NPC_H
#define NPC_H

#define MAXNPCSPEED 100

#include "../include/shapeactor.h"

class NPC : public ShapeActor
{
    public:
        NPC();
        NPC(NPC*);
        NPC(NPC*, float, float);
        NPC(float, float, float, float, int);
        virtual ~NPC();
        void update(int, Map*, sf::Time, float rotation=0);
        bool getPlayerHostile();
        void setPlayerHostile(bool);
    protected:
    private:
        bool playerHostile;
};

#endif // NPC_H
