#ifndef FOOD_H
#define FOOD_H
#include <cstdlib>
#include <time.h>
#include "objPos.h"
#include "objPosArrayList.h"

class Food{
    private:
        objPosArrayList* foodBucket;
        int xRange;
        int yRange;
    public:
        Food();
        Food(int boardSizeX, int boardSizeY);
        ~Food();
        void generateFood(objPosArrayList* blockOff);
        objPosArrayList* getFoodPos();
};

#endif