#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included
    objPos zPos;
    zPos.setObjPos(mainGameMechsRef->getBoardSizeX()/2, mainGameMechsRef->getBoardSizeY()/2, '@');
    playerPosAList = new objPosArrayList();
    playerPosList->insertHead(zPos);
    currentHead = zPos;
}


Player::~Player()
{
    // delete any heap members here
    delete playerPosList;
}

objPos Player::getPlayerPos() const
{
    // return the reference to the playerPos arrray list
    return playerPosList;
}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic 
    char input = mainGameMechsRef->getInput();
    if(input != 0)  // if not null character
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
}

// More methods to be added