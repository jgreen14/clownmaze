#include "../include/camera.h"
#include "../include/step.h"

Camera::Camera(Data* data, sf::RenderWindow* window)
{
    int i;

    width = data->getWidth();// * 0.5;
    height = data->getHeight();// * 0.6;
    renderWidth = data->getRenderWidth();
    renderHeight = data->getRenderHeight();
    //spacing = width / renderWidth;
    this->focalLength = 0.8;
    range = 23;
    lightRange = 12;
    scale = (renderWidth + renderHeight) / 1200;
    zbuffer = new float[renderWidth];
    for (i = 0; i < renderWidth; i++)
        zbuffer[i] = INFINITY;

    gameData = data;
    App = window;
    //view.reset(sf::FloatRect(0+100, 0, resX-200, resY));
    view.setCenter(sf::Vector2f(renderWidth/2, renderHeight/2));
    view.setSize(sf::Vector2f(width*renderHeight/height, renderHeight));
    //view.setSize(sf::Vector2f(data->getInternalRes()*1.5, resY*1.5));

    //Load wall textures
    texShapes = new sf::RectangleShape[gameData->getTextureCount()];
    for (i = 0; i < gameData->getTextureCount(); i++)
    {
        texShapes[i].setTexture(gameData->getTexture(i));
    }//for

    //Load item images
    //itemCount = gameData->getItemCount();
    //items = gameData->getItems();
}//Camera(int, int)

Camera::~Camera()
{
    //int i;

    delete[] texShapes;
    delete[] zbuffer;
}//~Camera

void Camera::render(Map* map, Player* player)
{
    int i;

    App->setView(view);

    //Draw the "sky" (this is the simplest way to do it)
    shape.setFillColor(sf::Color(135,206,235));
    shape.setSize(sf::Vector2f(this->renderWidth, this->renderHeight/2));
    shape.setPosition(0, 0);
    App->draw(shape);

    //Draw the floor (this is the simplest way to do it)
    shape.setFillColor(sf::Color(192,192,192));
    shape.setPosition(0, this->renderHeight/2);
    App->draw(shape);

    drawColumns(map, player);
    for (i = 0; i < map->getActorCount(); i++)
        drawSprite(map->getActor(i));//, 0, map, player);
}//render

void Camera::drawColumns(Map* map, Player* player)
{
    int i;
    float column;
    float x;
    float angle;
    float playerAngle;
    //int tempHit;

    for (column = 0; column < renderWidth; column++)
    {
        x = column / renderWidth - 0.5; //Gets a proportion between -0.5 & 0.5 (i.e., (0 to 1) - 0.5)
        angle = atan2(x, focalLength); //Gets the angle difference between the column proportion and the FOV
        playerAngle = fmodf(player->getDirection() + angle + CIRCLE, CIRCLE); //Make sure the playerAngle is between 0 and 2pi
        map->cast(player->getX(), player->getY(), player->getDirection() + angle, range);
        drawColumn(column, angle, map, player->getZ());
        for (i = 0; i < map->getActorCount(); i++)
        {
            getSpriteHit(column, playerAngle, map->getActor(i));
        }//for
        //drawSprites(column, player->getDirection() + angle, map, player);
        //std::cout << "Column:" << column << "Angle:" << angle << " X:" << x << std::endl;
    }//for
}//drawColumns

void Camera::drawColumn(int column, float angle, Map* map, float playerHeight)
{
    int s;
    int h = 3;
    Step* step;
    sf::Vector2f* wall;
    int left = column;//floor(column * spacing);
    //int width = ceil(spacing);
    int hit = -1;
    float lighting;
    float lightVal;
    int textureX;
    int texNum;
    //bool hasHit = false;
    float prevTop = this->renderHeight;
    float bottom = this->renderHeight;
    float texScale; //Scale factor used to determine what parts of the texture to draw
    float texHeight; //Height to resize texture

    //For each height level we find any hits on that level and draw the column
    //Draw from the bottom up and save the "highest" pixel so we don't draw the lower parts of columns we don't need
    for (h = 1; h <= map->getMaxHeight(); h++)
    //for (h = map->getMaxHeight(); h > 0; h--)
    {
        hit = -1;

        while (++hit < map->getStepCount() && map->getStep(hit)->getHeight() < h);

        for (s = map->getStepCount() - 1; s >= 0; s--)
        {
            step = map->getStep(s);

            if (s == hit)
            {
                //hasHit = true;

                //wall = project(step->getHeight(), angle, step->getDistance());
                wall = project(h, angle, step->getDistance(), playerHeight);
                bottom = wall->x + wall->y;

                //Draw the "floor" as a solid color if we're drawing the lowest height
                //if (h == 1)
                //    App->Draw(shape->Rectangle(left, wall->x + wall->y, left + width, this->renderHeight, sf::Color(192,192,192)));

                if (wall->x < prevTop)
                {
                    if (prevTop < bottom)
                    {
                        bottom = prevTop;
                    }//else

                    //Draw textured walls
                    texNum = floor(step->getHeight()-1);
                    textureX = floor(texShapes[texNum].getTexture()->getSize().x * step->getOffset());
                    //textureX = floor(1024 * step->getOffset());
                    texHeight = bottom - wall->x;
                    texScale = texHeight/wall->y; //Amount of wall to draw divided by the actual height of the wall
                    //std::cout << column << " " << width << " " << textureX << " " << texShapes[texNum].getTexture()->getSize().x << std::endl;
                    texShapes[texNum].setTextureRect(sf::IntRect(textureX, 0, 1, texShapes[texNum].getTexture()->getSize().y*texScale));
                    texShapes[texNum].setPosition(left, wall->x);
                    //texSprites[texNum].SetY(wall->x);
                    texShapes[texNum].setSize(sf::Vector2f(1, texHeight));

                    //Calculate shading level of lighting and draw the lighting box
                    lighting = (step->getDistance() + step->getShading()) / lightRange - map->getLight();
                    lighting > 0.1 ? lightVal = 256 - lighting * 128 : lightVal = 255;
                    texShapes[texNum].setFillColor(sf::Color(lightVal, lightVal, lightVal));

                    App->draw(texShapes[texNum]);//*/

                    //shape.setSize(sf::Vector2f(width, texHeight));
                    //shape.setPosition(left, wall->x);
                    //shape.setFillColor(sf::Color(0,192,0));
                    //Draw walls as a solid color
                    //App->draw(shape);

                    //App->draw(shape);

                    prevTop = wall->x;

                    if (h == 1)
                    {
                        zbuffer[column] = step->getDistance();
                    }//if
                }//if
                else
                    if (h == 1)
                        zbuffer[column] = INFINITY;

                //std::cout << "Column:" << column << " Angle:" << angle << " Left:" << left << " WallX:" << wall->x << " Width:" << width << " WallY:" << wall->y << " Light:" << lighting << " Hit:" << hit << std::endl;
                delete wall;
            }//if
        }//for*/
    }//for
}//drawColumn

//void Camera::getSpriteHit(int column, float angle, ItemShape* item)
void Camera::getSpriteHit(int column, float angle, ShapeActor* item)
{
    //int spriteAngleInt = (int)(item->getDirection()*500*renderWidth/960); //Use renderwidth to set precision of angle
    int spriteAngleInt = (int)(item->getAnglePlayer()*500*renderWidth/960);
    int playerAngleInt = (int)(angle*500*renderWidth/960); //Use renderwidth to set precision of angle
    bool hasHit = false;
    int i;
    //leftColumn = -1;
    //rightColumn = -1;

    //if (spriteAngleInt == playerAngleInt && item->getDistance() < range)
    if (spriteAngleInt == playerAngleInt && item->getDistancePlayer() < range)
    {
        item->setRightCol(column + item->getWidth()/2);
        item->setLeftCol(column - item->getWidth()/2);

        i = item->getLeftCol();
        //std::cout << column << " " << spriteAngleInt << " " << playerAngleInt << std::endl;
        while (hasHit == false && i <= item->getRightCol())
        {
            //if (i >= 0 && item->getDistance() < zbuffer[i])
            if (i >= 0 && item->getDistancePlayer() < zbuffer[i])
            {
                hasHit = true;
                item->setHit(column);
            }//if
            i++;
        }//while
    }//if
}//getSpriteHit

//void Camera::drawSprite(ItemShape* item)//, float angle, Map* map, Player* player)
void Camera::drawSprite(ShapeActor* item)
{
    int i = item->getLeftCol();
    bool leftHit = false;
    bool rightHit = false;
    int newLeftCol = item->getLeftCol();
    int newRightCol = item->getRightCol();

    float lighting;
    float lightVal;

    float spriteHeight; //The scaled height of the sprite
    //float z = item->getDistance();// * cos(angle);
    float z = item->getDistancePlayer();

    if (item->getHit() != -1)
    {
        //std::cout << column << " " << spriteQuadrant << " " << facingQuadrant << std::endl;
        //Use the same calculations as the project function to scale and find y position of sprite
        spriteHeight = item->getShape()->getTexture()->getSize().y / z * item->getScale();

        //newRightCol = rightColumn;
        while (!rightHit && i <= item->getRightCol())
        {
            //if (i >= 0 && !leftHit && item->getDistance() < zbuffer[i])
            if (i >= 0 && !leftHit && item->getDistancePlayer() < zbuffer[i])
            {
                newLeftCol = i;
                leftHit = true;
            }//if
            //else if (i >= 0 && leftHit && item->getDistance() > zbuffer[i])
            else if (i >= 0 && leftHit && item->getDistancePlayer() > zbuffer[i])
            {
                newRightCol = i;
                rightHit = true;
            }//else if
            i++;
        }//for*/

        if (leftHit) //Make sure there was actually a drawable part of the sprite
        {
            //std::cout << column << " " << (newLeftCol - leftColumn)*z << " " << (newRightCol - leftColumn)*z << " " << spriteWidth << std::endl;
            /*** MAKE SOME VARIABLES TO SIMPLIFY THESE CALCULATIONS ***/
            item->getShape()->setTextureRect(sf::IntRect((newLeftCol - item->getLeftCol())*z / item->getScale(), 0,
                    ((newRightCol - item->getLeftCol())*z - (newLeftCol - item->getLeftCol())*z) / item->getScale(), item->getShape()->getTexture()->getSize().y));
            item->getShape()->setSize(sf::Vector2f(item->getWidth()*((newRightCol-newLeftCol)/item->getWidth()), spriteHeight));
            item->getShape()->setPosition((item->getHit()+(newLeftCol - item->getLeftCol())) - item->getWidth()/2, this->renderHeight/2 * (1 + 1/z) - spriteHeight);
            //lighting = item->getDistance() / lightRange;
            lighting = item->getDistancePlayer() / lightRange;
            lighting > 0.1 ? lightVal = 256 - lighting * 128 : lightVal = 255;
            if (item->flashing())
                item->getShape()->setFillColor(sf::Color(lightVal, lightVal/2, lightVal/2));
            else
                item->getShape()->setFillColor(sf::Color(lightVal, lightVal, lightVal));
            App->draw(*item->getShape());
        }//if
    }//if
}//drawSprites

sf::Vector2f* Camera::project(float mapHeight, float angle, float distance, float playerHeight)
{
    float height = mapHeight; // 0;
    //if (mapHeight > 0)
    //    height = 1;

    float z = distance * cos(angle);
    //float wallHeight = this->renderHeight * height / z;
    float wallHeight = (this->renderHeight * 1 / z);
    //float bottom = this->renderHeight / 2 * (1 + 1 / z);
    float bottom = this->renderHeight / 2 * (1 + 1 / z) - (wallHeight * (height-1)) + (wallHeight * playerHeight);

    return new sf::Vector2f(bottom - wallHeight, wallHeight);
}//project
