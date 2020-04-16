#ifndef SHAPEACTOR_H
#define SHAPEACTOR_H

#define FLASHTIME 5

#include <SFML/Graphics.hpp>
#include "../include/actor.h"

class ShapeActor : public Actor
{
    public:
        ShapeActor();
        ShapeActor(ShapeActor*);
        ShapeActor(float, float, float, float, int);
        virtual ~ShapeActor();

        virtual void update(int, Map*, sf::Time, float) =0;
        sf::RectangleShape* getShape();
        int getHit();
        void setHit(int);
        float getWidth();
        int getRightCol();
        void setRightCol(int);
        int getLeftCol();
        void setLeftCol(int);
        float getScale();
        float getAnglePlayer();
        void setAnglePlayer(float, float);
        float getDistancePlayer(); //MOVE TO ITEM CLASS
        void setDistancePlayer(float, float);
        void updateShapeWidth();
        float getShapeWidth();
        int getImageIndex();
        void setImageIndex(int);
        virtual void takeDamage(int);
        bool flashing();
    protected:
        sf::RectangleShape* shape;
        int shapeHit;
        float shapeWidth;
        int rightColumn;
        int leftColumn;
        int flashCounter;
        float shapeScale;
        float distancePlayer; //MOVE TO ITEM CLASS
        float anglePlayer; //MOVE TO ITEM CLASS
        int imageIndex;
    private:
};

#endif // SHAPEACTOR_H
