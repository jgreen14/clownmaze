#include "../include/data.h"
#include "../include/map.h"

Data::Data(Player* player)
{
    texCount = 0;
    imageCount = 0;
    itemCount = 0;
    npcCount = 0;
    mapCount = 0;
    width = 640;
    height = 480;
    renderWidth = 960;
    renderHeight = 540;
    this->player = player;
}//Data

Data::~Data()
{
    int i;

    for (i = 0; i < texCount; i++)
        delete textures[i];
    delete[] textures;

    for (i = 0; i < imageCount; i++)
        delete images[i];
    delete[] images;

    for (i = 0; i < mapCount; i++)
        delete maps[i];
    delete[] maps;

    for (i = 0; i < itemCount; i++)
        delete items[i];
    delete[] items;

    for (i = 0; i < npcCount; i++)
        delete npcs[i];
    delete[] npcs;
}//~Data

void Data::load()
{
    loadSettings();
    loadTextures();
    loadImages();
    loadItems(); //Must be done after loadImages
    loadNPCs();
    loadMaps(); //Must be done after loadItems
}//load

void Data::loadTextures()
{
    int i;
    std::string texNames[MAXTEXTURES];
    std::string line;
    std::ifstream file("data/textures.dat");

    if (file.is_open())
    {
        std::cout << "Loading textures..." << std::endl;
        getline(file, line);
        while (line.compare("ENDFILE") != 0)
        {
            texNames[texCount] = line;
            texCount++;
            getline(file, line);
        }//while

        textures = new sf::Texture*[texCount];

        for (i = 0; i < texCount; i++)
        {
            std::cout << texNames[i] << std::endl;
            textures[i] = new sf::Texture();
            textures[i]->loadFromFile(texNames[i]);
            textures[i]->setSmooth(false);
        }//for
    }//if
}//loadTextures

void Data::loadImages()
{
    int i;
    std::string imageNames[MAXIMAGES];
    std::string line;
    std::ifstream file("data/images.dat");
    sf::Image tempImage;

    if (file.is_open())
    {
        std::cout << "Loading images..." << std::endl;
        getline(file, line);
        while (line.compare("ENDFILE") != 0)
        {
            imageNames[imageCount] = line;
            imageCount++;
            getline(file, line);

        }//while

        images = new sf::Texture*[imageCount];

        for (i = 0; i < imageCount; i++)
        {
            std::cout << imageNames[i] << std::endl;
            tempImage.loadFromFile(imageNames[i]);
            tempImage.createMaskFromColor(sf::Color(255,0,255),0);
            tempImage.createMaskFromColor(sf::Color(0,255,255),0);

            images[i] = new sf::Texture();
            images[i]->loadFromImage(tempImage);
            images[i]->setSmooth(false);
        }//for
    }//if
}//loadTextures

void Data::loadMaps()
{
    int splits[2];
    int mapSize;
    int randomize = 0;
    int x, y, z;
    int index;
    float posX, posY;

    std::string line;
    std::ifstream file("data/maps.dat");

    if (file.is_open())
    {
        maps = new Map*[MAXMAPS];
        std::cout << "Loading maps..." << std::endl;
        getline(file, line);
        while (mapCount < MAXMAPS && line.compare("ENDFILE") != 0)
        {
            mapSize = atoi(line.c_str());

            getline(file, line);
            randomize = atoi(line.c_str());

            maps[mapCount] = new Map(mapSize);

            if (randomize)
                maps[mapCount]->generate();
            maps[mapCount]->createWalls();

            getline(file, line);
            while (line.compare("ENDITEMS") != 0)
            {
                splits[0] = line.find(':');
                splits[1] = line.find(':', splits[0]+1);

                index = atoi(line.substr(0,splits[0]).c_str());
                posX = atoi(line.substr(splits[0]+1,splits[1]).c_str()) * 0.1;
                posY = atoi(line.substr(splits[1]+1,line.length()).c_str()) * 0.1;
                maps[mapCount]->add(new Item(items[index], posX, posY));

                getline(file, line);
            }//while

            getline(file, line);
            while (line.compare("ENDNPCS") != 0)
            {
                splits[0] = line.find(':');
                splits[1] = line.find(':', splits[0]+1);

                index = atoi(line.substr(0,splits[0]).c_str());
                posX = atoi(line.substr(splits[0]+1,splits[1]).c_str()) * 0.1;
                posY = atoi(line.substr(splits[1]+1,line.length()).c_str()) * 0.1;
                maps[mapCount]->add(new NPC(npcs[index], posX, posY));

                getline(file, line);
            }//while

            getline(file, line);
            while (line.compare("ENDMAP") != 0)
            {
                splits[0] = line.find(':');
                splits[1] = line.find(':', splits[0]+1);

                x = atoi(line.substr(0,splits[0]).c_str());
                y = atoi(line.substr(splits[0]+1,splits[1]).c_str());
                z = atoi(line.substr(splits[1]+1,line.length()).c_str());
                if (z > maps[mapCount]->getMaxHeight())
                    maps[mapCount]->setMaxHeight(z);
                maps[mapCount]->setHeight(x, y, z);

                getline(file, line);
            }//while

            mapCount++;
            getline(file, line);
        }//while
    }//if
}//loadMaps

void Data::loadItems()
{
    int splits[2];
    int imageIndex, value;
    ITEMTYPE type;
    std::string line;
    std::ifstream file("data/items.dat");

    if (file.is_open())
    {
        items = new Item*[MAXITEMS];
        std::cout << "Loading items..." << std::endl;
        getline(file, line);
        while (itemCount < MAXITEMS && line.compare("ENDFILE") != 0)
        {
            splits[0] = line.find(':');
            splits[1] = line.find(':', splits[0]+1);

            imageIndex = atoi(line.substr(0,splits[0]).c_str());
            value = atoi(line.substr(splits[0]+1,splits[1]).c_str());
            type = (ITEMTYPE)atoi(line.substr(splits[1]+1,line.length()).c_str());

            items[itemCount] = new Item(0,0,0,0,renderWidth);
            items[itemCount]->setValue(value);
            items[itemCount]->setType(type);
            items[itemCount]->getShape()->setTexture(getImage(imageIndex));

            itemCount++;
            getline(file, line);
        }//while
    }//if
}//loadItems

void Data::loadNPCs()
{
    int splits[2];
    int imageIndex, hp;
    bool hostile;
    std::string line;
    std::ifstream file("data/npcs.dat");

    if (file.is_open())
    {
        npcs = new NPC*[MAXNPCS];
        std::cout << "Loading npcs..." << std::endl;
        getline(file, line);
        while (npcCount < MAXNPCS && line.compare("ENDFILE") != 0)
        {
            splits[0] = line.find(':');
            splits[1] = line.find(':', splits[0]+1);

            imageIndex = atoi(line.substr(0,splits[0]).c_str());
            hp = atoi(line.substr(splits[0]+1,splits[1]).c_str());
            hostile = atoi(line.substr(splits[1]+1,line.length()).c_str());

            npcs[npcCount] = new NPC(0,0,0,0,renderWidth);
            npcs[npcCount]->setHP(hp);
            npcs[npcCount]->setPlayerHostile(hostile);
            npcs[npcCount]->getShape()->setTexture(getImage(imageIndex));

            npcCount++;
            getline(file, line);
        }//while
    }//if
}//loadItems

void Data::loadSettings()
{
    std::string line;
    std::ifstream file("data/settings.dat");
    int splitPos;

    if (file.is_open())
    {
        std::cout << "Loading settings..." << std::endl;
        getline(file, line);
        while (line.compare("ENDFILE") != 0)
        {
            splitPos = line.find(':');

            std::cout << line << std::endl;
            if (line.substr(0,splitPos).compare("WIDTH") == 0)
                width = atoi(line.substr(splitPos+1).c_str());
            else if (line.substr(0,splitPos).compare("HEIGHT") == 0)
                height = atoi(line.substr(splitPos+1).c_str());
            else if (line.substr(0,splitPos).compare("RENDERWIDTH") == 0)
                renderWidth = atoi(line.substr(splitPos+1).c_str());
            else if (line.substr(0,splitPos).compare("RENDERHEIGHT") == 0)
                renderHeight = atoi(line.substr(splitPos+1).c_str());
            else if (line.substr(0,splitPos).compare("MAPSIZE") == 0)
                mapSize = atoi(line.substr(splitPos+1).c_str());

            getline(file, line);
        }//while
    }//if
}//loadSettings

sf::Texture* Data::getTexture(int num)
{
    //if (num >= 0 && num < texCount)
        return textures[num];
    //else
    //    return sf::Image;
}//getTexture

int Data::getTextureCount()
{
    return texCount;
}//getTextureCount

sf::Texture* Data::getImage(int num)
{
    //if (num >= 0 && num < texCount)
        return images[num];
    //else
    //    return sf::Image;
}//getTexture

int Data::getImageCount()
{
    return imageCount;
}//getTextureCount

NPC* Data::getNPC(int npc)
{
    return npcs[npc];
}//getNPC

int Data::getNPCCount()
{
    return npcCount;
}//getNPCCount

Item* Data::getItem(int item)
{
    return items[item];
}//getItem

int Data::getItemCount()
{
    return itemCount;
}//getItemCount

Map* Data::getMap(int mapNum)
{
    return maps[mapNum];
}//getMap

int Data::getMapCount()
{
    return mapCount;
}//getMapCount

int Data::getWidth()
{
    return width;
}//getResX

int Data::getHeight()
{
    return height;
}//getResY

int Data::getRenderWidth()
{
    return renderWidth;
}//getInternalRes

int Data::getRenderHeight()
{
    return renderHeight;
}//getRenderHeight
