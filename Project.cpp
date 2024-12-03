#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"
#include "GameMechs.h"
#include "Food.h"
#include "objPosArrayList.h"

using namespace std;

#define DELAY_CONST 100000
#define ESC 27

//global pointers to instantiate on heap
Player *myPlayer;
GameMechs *myGameMechs;
Food *myFood;

bool exitFlag;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();

    while(myGameMechs->getExitFlagStatus() == false)  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    myGameMechs = new GameMechs();
    myFood = new Food(myGameMechs->getBoardSizeX(), myGameMechs->getBoardSizeY());
    myPlayer = new Player(myGameMechs, myFood);
    objPosArrayList* tempPosList;
    tempPosList = myPlayer->getPlayerPos();

    myFood->generateFood(tempPosList);  //initialize food item coord

    exitFlag = false;
}

void GetInput(void)
{
   if (MacUILib_hasChar())
   {
        char input = MacUILib_getChar();
        myGameMechs->setInput(input);
   }
}

void RunLogic(void)
{
    if(myGameMechs->getInput() == ESC){
        myGameMechs->setExitTrue();
    }
    else{
        myPlayer->updatePlayerDir();
        myPlayer->movePlayer();
    }
    myGameMechs->clearInput();
}

void DrawScreen(void)
{
    MacUILib_clearScreen();    

    bool finished;
    int totRow = myGameMechs->getBoardSizeY();
    int totCol = myGameMechs->getBoardSizeX();

    objPosArrayList* playerBody = myPlayer->getPlayerPos();
    objPos tempBody;

    objPosArrayList *temoFoodList = myFood->getFoodPos();
    objPos tempFoodPos;

    for(int i = 0; i <totRow; i++){
        for(int j = 0; j < totCol; j++){
            finished = false;
            for (int k = 0; k < playerBody->getSize(); k++){
                tempBody = playerBody->getElement(k);
                if (tempBody.pos->x == j && tempBody.pos->y == i){
                    MacUILib_printf("%c",tempBody.symbol);
                    finished = true;
                    break;
                }
            }
            if (!finished){
                for (int m = 0; m < temoFoodList->getSize(); m++){
                    tempFoodPos = temoFoodList->getElement(m);
                    if(tempFoodPos.pos->x == i && tempFoodPos.pos->y == j){
                        MacUILib_printf("%c", tempFoodPos.symbol);
                        finished = true;
                        break;
                    }
                }
            }
            if(finished){
                continue;
            }
            if(j == 0 || j == totCol -1 || i == 0 || i == totRow - 1){
                if(j == totCol - 1){
                    MacUILib_printf("#\n");
                }
                else{
                    MacUILib_printf("#");
                }
            }
            else{
                MacUILib_printf(" ");
            }
        }
    }
    MacUILib_printf("Score: %d \n", myGameMechs->getScore());

    MacUILib_printf("=====DEBUG MESSAGES=====\n");
    MacUILib_printf("Player Positions:\n");
    for (int z = 0; z < playerBody->getSize(); z++){
        tempBody = playerBody->getElement(z);
        MacUILib_printf("[%d,%d]\n", tempBody.pos->x, tempBody.pos->y);
    }
    MacUILib_printf("Board Size: %dx%d", myGameMechs->getBoardSizeX(), myGameMechs->getBoardSizeY());

}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();  
    if (myGameMechs->getLoseFlagStatus()){
        MacUILib_printf("Game Over...\n");
    }  
    else if(myGameMechs->getExitFlagStatus()){
        MacUILib_printf("Game exited!\n");
    }
    MacUILib_printf("Final score: %d\n", myGameMechs->getScore());

    delete myPlayer;
    delete myFood;
    delete myGameMechs;

    MacUILib_uninit();
}
