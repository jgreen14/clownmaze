#include "../include/game.h"

Game::Game()
{
    player = new Player(10.5, 2.5, 0, PI * 0.3);
    gameData = new Data(player);
    gameData->load();

    //Create the main window
    window = new sf::RenderWindow(sf::VideoMode(gameData->getWidth(), gameData->getHeight()), "raycast");
    window->setVerticalSyncEnabled(true);
    window->setMouseCursorVisible(false);

    camera = new Camera(gameData, window);
    input = new Input();
    currentMap = 0;
    map = gameData->getMap(currentMap);
}//game

Game::~Game()
{
    delete input;
    delete camera;
    delete window;
    delete gameData;
    delete player;
}//~game

void Game::gameLoop()
{
    int i, j;
    int inputVal = 0;
    float dist;
    ShapeActor* tempActor1;
    ShapeActor* tempActor2;
    Bullet* tempBullet;
    sf::Time elapsed;

    // Start game loop
    while (window->isOpen())
    {
        elapsed = clock.restart();

        // Process events
        while (window->pollEvent(event))
        {
            switch (input->processEvent(&event))
            {
                case CLOSEWINDOW:
                case QUIT:
                    window->close();
                    break;
                case NEXTMAP:
                    if (currentMap < gameData->getMapCount() - 1)
                    {
                        currentMap++;
                        changeMap();
                    }//if
                    break;
                case PREVMAP:
                    if (currentMap > 0)
                    {
                        currentMap--;
                        changeMap();
                    }//if
                    break;
                case MOUSEBUTTONLEFT:
                    tempBullet = new Bullet(player->getX(), player->getY(), player->getZ(), player->getDirection(), player->getXSpeed(), player->getYSpeed(), gameData->getRenderWidth());
                    tempBullet->getShape()->setTexture(gameData->getImage(2));
                    map->add(tempBullet);
                    break;
                default:
                    break;
            }//switch
        }//while

        inputVal = input->processInput(window);

        player->update(inputVal, map, elapsed, (float)input->getMouseDeltaX()/window->getSize().x);

        //Update distance and direction of items from player
        for (i = 0; i < map->getActorCount(); i++)
        {
            tempActor1 = map->getActor(i);
            tempActor1->setDistancePlayer(player->getX(), player->getY());
            tempActor1->setAnglePlayer(player->getX(), player->getY());
            tempActor1->updateShapeWidth();

            tempActor1->update(0, map, elapsed, 0);

            if (tempActor1->actorType() == BULLET)
            {
                //Check if bullets hit anything
                for (j = 0; j < map->getActorCount(); j++)
                {
                    tempActor2 = map->getActor(j);
                    dist = distance(tempActor1, tempActor2);
                    if (i != j && dist < 0.1)
                    {
                        if (tempActor2->actorType() == NONPLAYER)
                        {
                            ((ShapeActor*)tempActor2)->takeDamage(((Bullet*)tempActor1)->getDamage());
                            tempActor1->deactivate();
                        }//if
                    }//if
                }//for
            }//if

            if (tempActor1->isActive() == false)
                map->remove(i);
        }//for

        sortShapeActors((ShapeActor**)map->getActors(), map->getActorCount());

        //Display the game
        window->clear();
        camera->render(map, player); //Render the player's current view
        window->setView(window->getDefaultView());
        window->display();
    }//while
}//gameLoop

//Use a Shell sort to sort ShapeActors by distance from player
void Game::sortShapeActors(ShapeActor** items, int itemCount)
{
    int i;
    int numLength = itemCount;
    //ItemShape* temp;
    ShapeActor* temp;
    bool flag = true;
    int d = numLength;

    while(flag || (d > 1))      // boolean flag (true when not equal to 0)
    {
        flag = false;           // reset flag to 0 to check for future swaps
        d = (d+1) / 2;
        for (i = 0; i < (numLength - d); i++)
        {
            if (items[i + d]->getDistancePlayer() > items[i]->getDistancePlayer())
            {
                temp = items[i + d];      // swap positions i+d and i
                items[i + d] = items[i];
                items[i] = temp;
                flag = true;                  // tells swap has occurred
            }//if
        }//for
    }//while
}//sortItems

float Game::distance(ShapeActor* actor1, ShapeActor* actor2)
{
    float xDiff = actor1->getX() - actor2->getX();
    float yDiff = actor1->getY() - actor2->getY();
    float dist = sqrt((xDiff*xDiff)+(yDiff*yDiff));

    return dist;
}//distance

void Game::changeMap()
{
    map = gameData->getMap(currentMap);
    //Will also need to reset the player position to map start position
}//changeMap
