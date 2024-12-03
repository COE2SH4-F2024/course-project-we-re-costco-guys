#include "Player.h"
#define w 119
#define a 97
#define s 115
#define d 100

Player::Player(GameMechs* thisGMRef, Food* thisFoodRef)
{
    mainGameMechsRef = thisGMRef;
    foodRe = thisFoodRef;
    myDir = STOP;

    // more actions to be included
    objPos tempPos;
    //initialize player pos, symbol
    tempPos.setObjPos(mainGameMechsRef->getBoardSizeX()/2, mainGameMechsRef->getBoardSizeY()/2, '@');
    //create list for snake body on heap
    playerPosAList = new objPosArrayList();
    playerPosAList->insertHead(tempPos);
    currentHead = tempPos;
}


Player::~Player()
{
    // delete any heap members here
    delete playerPosAList;
}

objPosArrayList* Player::getPlayerPos()
{
    // return the reference to the playerPos arrray list
    return playerPosAList;
}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic 
    char input = mainGameMechsRef->getInput();
    if(input != 0) 
    {
        switch(input)
        {                         
            case w:
                if(myDir == STOP || myDir == LEFT || myDir == RIGHT){
                    myDir = UP;
                }
                break;
            case a:
                if(myDir == STOP || myDir == UP || myDir == DOWN){
                    myDir = LEFT;
                }
                break;
            case s:
                if(myDir == STOP || myDir == LEFT || myDir == RIGHT){
                    myDir = DOWN;
                }
                break;
            case d:
                if(myDir == STOP || myDir == UP || myDir == DOWN){
                    myDir = RIGHT;
                }
                break;
            default:
                break;
        }
        mainGameMechsRef->clearInput();
    }         
}

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic
    //create temporary food list storing food item coord
    objPosArrayList *tempFoodList = foodRe->getFoodPos();
    objPos tempFoodPos;
    updateCurrentHead();
    playerPosAList->insertHead(currentHead);
    //check snake body collision flag
    bool collide = false;
    for (int i = 0; i < tempFoodList->getSize(); i++){
        tempFoodPos = tempFoodList->getElement(i);
        
        //normal food item
        if(currentHead.isPosEqual(&tempFoodPos)&& tempFoodPos.getSymbol() == 'O'){
            foodRe->generateFood(playerPosAList);   //regenerate food item
            mainGameMechsRef->incrementScore();  //add 1 score for each normal food item
            collide = true;
            break;
        }

        //bonus food item '!', gives 10 points no change to size
        else if (currentHead.isPosEqual(&tempFoodPos) && tempFoodPos.getSymbol() == '!'){
            foodRe->generateFood(playerPosAList);
            for (int j = 0; j < 10; j++){
                mainGameMechsRef->incrementScore();
            }
            playerPosAList->removeHead();
            collide = true;
            break;
        }
        //bonus food '^', adds 50 points and increases 10 times the size
        else if(currentHead.isPosEqual(&tempFoodPos) && tempFoodPos.getSymbol() == '^'){
            foodRe->generateFood(playerPosAList);
            for (int k = 0; k < 50; k++){
                mainGameMechsRef->incrementScore();
            }
            for (int m = 0; m < 10; m++){
                playerPosAList->insertTail(playerPosAList->getTailElement());
            }
            collide = true;
            break;
        }
    }
    if (!collide){
        playerPosAList->removeTail();
    }
    if(checkCollision()){
        mainGameMechsRef->setExitTrue();
        mainGameMechsRef->setLoseFlag();
    }

}

// More methods to be added
void Player::updateCurrentHead()
{
    currentHead = playerPosAList->getHeadElement();
    int colSize = mainGameMechsRef->getBoardSizeY();    //max col
    int rowSize = mainGameMechsRef->getBoardSizeX();    //max row

    switch(myDir){
        case UP:
            currentHead.pos->y--;
            if(currentHead.pos->y == 0)currentHead.pos->y = colSize-2;
            break;
        
        case DOWN:
            currentHead.pos->y++;
            if (currentHead.pos->y == colSize-1)currentHead.pos->y = 1;
            break;
        
        case LEFT:
            currentHead.pos->x--;
            if (currentHead.pos->x == 0)currentHead.pos->x = rowSize-2;
            break;
        
        case RIGHT:
            currentHead.pos->x++;
            if(currentHead.pos->x == rowSize-1)currentHead.pos->x = 1;
            break;
    }
}

bool Player::checkCollision()
{
    objPos headElement, bodyElement;
    headElement = playerPosAList->getHeadElement();
    for (int i = 1; i < playerPosAList->getSize(); i++){
        bodyElement = playerPosAList->getElement(i);
        if(headElement.isPosEqual(&bodyElement))return true;
    }
    return false;
}