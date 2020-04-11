#ifndef CAMERA_H
#define CAMERA_H

#include <vector>
#include "../include/data.h"
#include "../include/map.h"
#include "../include/player.h"
#include "../include/item.h"
#include "../include/enum.h"

class Camera
{
    public:
        Camera(Data*, sf::RenderWindow*);
        virtual ~Camera();
        void render(Map*, Player*);
        void drawColumns(Map*, Player*);
        void drawColumn(int, float, Map*, float);
        //void drawSprite(ItemShape*);//, float, Map*, Player*);
        void drawSprite(ShapeActor*);
        sf::Vector2f* project(float, float, float, float);
    protected:
    private:
        sf::RenderWindow* App;
        sf::View view;
        sf::RectangleShape shape;
        sf::RectangleShape* texShapes;
        Data* gameData;
        //Item** items;
        //int getQuadrant(float);
        void getSpriteHit(int, float, ShapeActor*);
        //void sortItems();
        //int itemCount;
        float* zbuffer; //Distance buffer
        float spacing;
        float focalLength;
        float scale;
        float width;
        float height;
        int renderWidth;
        int renderHeight;
        int range;
        int lightRange;
};

#endif // CAMERA_H
