#ifndef DATA_H
#define DATA_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include "../include/item.h"
#include "../include/npc.h"
#include "../include/player.h"

class Data
{
    public:
        Data(Player*);
        virtual ~Data();
        void load();
        sf::Texture* getTexture(int);
        int getTextureCount();
        sf::Texture* getImage(int);
        int getImageCount();
        NPC* getNPC(int);
        int getNPCCount();
        Item* getItem(int);
        int getItemCount();
        Map* getMap(int);
        int getMapCount();
        int getWidth();
        int getHeight();
        int getRenderWidth();
        int getRenderHeight();
        int getMapSize();
    protected:
    private:
        void loadTextures();
        void loadSettings();
        void loadMaps();
        void loadItems();
        void loadImages();
        void loadNPCs();

        sf::Texture** textures;
        int texCount;
        sf::Texture** images;
        int imageCount;
        NPC** npcs;
        int npcCount;
        Item** items;
        int itemCount;
        Map** maps;
        int mapCount;
        Player* player; //THIS IS ONLY TEMPORARY UNTIL ITEM IS CHANGED NOT TO RELY ON PLAYER
        int width;
        int height;
        int renderWidth;
        int renderHeight;
        int mapSize;
};

#endif // DATA_H
