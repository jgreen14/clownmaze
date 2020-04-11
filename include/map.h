#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <string>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "../include/enum.h"

class Step;
class ShapeActor;

class Map
{
    public:
        Map(int);
        virtual ~Map();
        int get(float, float);
        void setHeight(int, int, int);
        void changeHeight(int, int, int);
        void createWalls();
        void generate();
        void cast(float, float, float, int);
        int getStepCount();
        Step* getStep(int);
        int getLight();
        int getMaxHeight();
        void setMaxHeight(int);
        ShapeActor** getActors();
        ShapeActor* getActor(int);
        int getActorCount();
        void add(ShapeActor*);
        void remove(int);
    protected:
    private:
        void step(Step*, float, float, float, float, bool);
        void inspect(Step*, int, int, float, float);

        Step* steps[MAXSTEPS];
        ShapeActor* actors[MAXACTORS];
        int actorCount;
        float currCos;
        float currSin;
        int stepCount;
        int size;
        int* wallGrid;
        int light;
        int maxHeight;
};

#endif // MAP_H
