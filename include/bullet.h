#ifndef BULLET_H
#define BULLET_H

#define MAXBULLETSPEED 100
#define BULLETACCEL 50

#include "../include/shapeactor.h"

class Bullet : public ShapeActor
{
    public:
        Bullet();
        Bullet(float, float, float, float, float, float, int);
        virtual ~Bullet();
        void update(int, Map*, sf::Time, float rotation=0);
        int getDamage();
    protected:
    private:
        int damage;
};

#endif // BULLET_H
