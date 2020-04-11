#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "../include/camera.h"
#include "../include/input.h"
#include "../include/map.h"
#include "../include/player.h"
#include "../include/bullet.h"
#include "../include/enum.h"

class Game
{
    public:
        Game();
        virtual ~Game();
        void gameLoop();
    protected:
    private:
        sf::Event event;
        sf::RenderWindow* window;
        Camera* camera;
        Input* input;
        int currentMap;
        Map* map;
        Player* player;
        Data* gameData;
        sf::Clock clock;

        void changeMap();
        float distance(ShapeActor*, ShapeActor*);
        void sortShapeActors(ShapeActor**, int);
};

#endif // GAME_H
