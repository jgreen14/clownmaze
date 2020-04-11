#ifndef ITEM_H
#define ITEM_H

#include "../include/shapeactor.h"

class Item : public ShapeActor
{
    public:
        Item();
        Item(Item*);
        Item(Item*, float, float);
        Item(float, float, float, float, int);
        virtual ~Item();
        void update(int, Map*, sf::Time, float rotation=0);
        int getValue();
        void setValue(int);
        ITEMTYPE getType();
        void setType(ITEMTYPE);
    protected:
    private:
        int value;
        ITEMTYPE type;
};

#endif // ITEM_H
