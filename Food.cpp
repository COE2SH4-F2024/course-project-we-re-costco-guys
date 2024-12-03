#include "Food.h"

Food::Food()
{
    objPos foodPos;    //initialize the food objects outside
    foodPos.setObjPos(-1, -1, 'O');
    foodBucket = new objPosArrayList();     //create a new object array list on heap
    foodBucket->insertHead(foodPos);    //add food object to head of array list
    xRange = 20;
    yRange = 20;
    srand(time(NULL));
}

Food::Food(int boardSizeX, int boardSizeY)
{
    objPos foodPos;
    foodPos.setObjPos(-1, -1, 'O');
    foodBucket = new objPosArrayList();
    foodBucket->insertHead(foodPos);
    xRange = boardSizeX;
    yRange = boardSizeY;
    srand(time(NULL));
}

Food::~Food()
{
    delete foodBucket;  //deallocate mem from heap
}

void Food::generateFood(objPosArrayList* blockOff)
{
    int randx, randy;
    bool overlap;
    objPos tempElementPos, tempFoodPos;
    do{
        overlap = false;
        while (foodBucket->getSize() > 0){
            foodBucket-> removeTail();
        }
        //generate food items
        for (int i = 0; i < 5; i++){
            objPos newFoodPos;
            randx = (rand()%(xRange - 2))+1;
            randy = (rand()%(yRange -2))+1;
            char foodSymbol;
            if (i < 3)foodSymbol = 'O'; //generate 3 normal food items
            else{
                if (rand()%2 == 0){
                    foodSymbol = '!';   //generate special food with 10 pts, no effect on size
                }
                else{
                    foodSymbol = '^';   //50 points, 10 times size
                }
            }
            newFoodPos.setObjPos(randx, randy, foodSymbol);
            for (int j = 0; j <= i; j++){
                foodBucket->getElement(j);
                if (tempFoodPos.isPosEqual(&newFoodPos)){
                    overlap = true;
                    break;
                }
            }
            if(overlap){
                break;
            }
            foodBucket->insertTail(newFoodPos);
        }
        for (int k = 0; k < blockOff->getSize(); k++){
            tempElementPos = blockOff->getElement(k);
            for(int m = 0; m < foodBucket->getSize(); m++){
                tempFoodPos = foodBucket->getElement(m);
                if(tempFoodPos.isPosEqual(&tempElementPos)){
                    overlap = true;
                    break;
                }
            }
        } 
        }while(overlap);
}

objPosArrayList* Food::getFoodPos(){
    return foodBucket;
}