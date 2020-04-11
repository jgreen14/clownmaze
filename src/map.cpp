#include "../include/map.h"
#include "../include/step.h"
#include "../include/shapeactor.h"

Map::Map(int mapSize)
{
    int i;

    size = mapSize;
    wallGrid = new int[size*size];
    for (i = 0; i < size*size; i++)
        wallGrid[i] = 0;
    srand(time(NULL));
    stepCount = 0;
    currCos = 0;
    currSin = 0;
    light = 0;
    maxHeight = 3;
    for (i = 0; i < MAXSTEPS; i++)
        steps[i] = new Step();
    actorCount = 0;
}//Map(int)

Map::~Map()
{
    int i;

    delete[] wallGrid;
    for (i = 0; i < MAXSTEPS; i++)
        delete steps[i];
    for (i = 0; i < actorCount; i++)
        delete actors[i];
    //delete[] steps;
}//~Map

int Map::get(float x, float y)
{
    //Multiplying or dividing these values will change the size of the tile/column
    int mapX = floor(x);
    int mapY = floor(y);

    if (mapX < 0 || mapX > this->size - 1 || mapY < 0 || mapY > this->size - 1)
        return -1;
    return this->wallGrid[mapY * this->size + mapX];
}//get

void Map::setHeight(int x, int y, int height)
{
    if (x > 0 && x < this->size && y > 0 && y < this->size)
    {
        this->wallGrid[y * this->size + x] = height;
    }//if
}//setHeight

void Map::changeHeight(int x, int y, int dHeight)
{
    if (x > 0 && x < this->size && y > 0 && y < this->size)
    {
        this->wallGrid[y * this->size + x] += dHeight;
    }//if
}//changeHeight

void Map::generate()
{
    int i;
    float random;

    for (i = 0; i < this->size * this->size; i++)
    {
        random = rand() % 100;

        if (random < 15)
            this->wallGrid[i] = 1;
        else if (random < 30)
            this->wallGrid[i] = 2;
    }//for*/
}//generate

void Map::createWalls()
{
    int i;

    //Draw outer walls
    for (i = 0; i < this->size; i ++)
    {
        this->wallGrid[i] = 3;
        this->wallGrid[this->size*i] = 3;
        this->wallGrid[this->size*(this->size - 1)+i] = 3;
        this->wallGrid[this->size*(i+1)-2] = 3;
    }//for
}//createWalls

void Map::cast(float x, float y, float angle, int range)
{
    Step* origin;
    Step* nextStep;
    Step* stepX = new Step();
    Step* stepY = new Step();

    currSin = sin(angle);
    currCos = cos(angle);

    stepCount = 0;
    steps[stepCount]->setX(x);
    steps[stepCount]->setY(y);

    do
    {
        origin = steps[stepCount];
        stepCount++;
        nextStep = steps[stepCount];

        step(stepX, currSin, currCos, origin->getX(), origin->getY(), false);
        step(stepY, currCos, currSin, origin->getY(), origin->getX(), true);

        if (stepX->getLength2() < stepY->getLength2())
        {
            stepX->copy(nextStep);
            inspect(nextStep, 1, 0, origin->getDistance(), stepX->getY());
        }//if
        else
        {
            stepY->copy(nextStep);
            inspect(nextStep, 0, 1, origin->getDistance(), stepY->getX());
        }//else

    } while (nextStep->getDistance() <= range);

    delete stepX;
    delete stepY;
}//step

void Map::step(Step* newStep, float rise, float run, float x, float y, bool inverted)
{
    float dx;
    float dy;

    if (run == 0)
    {
        newStep->setLength2(INFINITY);
    }//if
    else
    {
        dx = run > 0 ? floor(x + 1) - x : ceil(x - 1) - x;
        dy = dx * (rise/run);

        if (inverted)
        {
            newStep->setX(y + dy);
            newStep->setY(x + dx);
        }//if
        else
        {
            newStep->setX(x + dx);
            newStep->setY(y + dy);
        }//else
        newStep->setLength2(dx * dx + dy * dy);
    }//else
}//step

void Map::inspect(Step* step, int shiftX, int shiftY, float distance, float offset)
{
    int dx = currCos < 0 ? shiftX : 0;
    int dy = currSin < 0 ? shiftY : 0;

    step->setHeight(this->get(step->getX() - dx, step->getY() - dy));
    if (step->getLength2() != INFINITY)
        step->setDistance(distance + sqrt(step->getLength2()));
    else
        step->setDistance(INFINITY);

    //Shading determines what the shading for different sides of a map tile are
    if (shiftX)
        step->setShading(currCos < 0 ? 2 : 0);
    else
        step->setShading(currSin < 0 ? 2 : 1);

    step->setOffset(offset - floor(offset));
}//inspect

int Map::getStepCount()
{
    return stepCount;
}//getStepCount

Step* Map::getStep(int step)
{
    if (step <= stepCount)
        return steps[step];
    else
        return NULL;
}//getStep

int Map::getLight()
{
    return light;
}//getLight

int Map::getMaxHeight()
{
    return maxHeight;
}//getMaxHeight

void Map::setMaxHeight(int height)
{
    maxHeight = height;
}//setMaxHeight

ShapeActor** Map::getActors()
{
    return actors;
}//getItems

ShapeActor* Map::getActor(int index)
{
    return actors[index];
}//getItem

int Map::getActorCount()
{
    return actorCount;
}//getItemCount

void Map::add(ShapeActor* actor)
{
    actors[actorCount] = actor;
    actorCount = (actorCount + 1) % MAXACTORS;
}//addItem

void Map::remove(int index)
{
    int i;
    delete actors[index];
    for (i = index; i < actorCount - 1; i++)
        actors[i] = actors[i+1];
    actorCount--;
}//removeItem
