#include "GameMechs.h"
#include "MacUILib.h"
#include <time.h>
GameMechs::GameMechs()
{
   input = ' ';
   score = 0;
   exitFlag = false;
   loseFlag = false;
   boardSizeX = 20;
   boardSizeY = 10;
   srand(time(NULL)); 
}

GameMechs::GameMechs(int boardX, int boardY)
{
   input = ' ';
   score = 0;
   exitFlag = false;
   loseFlag = false;
   boardSizeX = boardX;
   boardSizeY = boardY;
   srand(time(NULL)); 
}

// do you need a destructor?
//nah

bool GameMechs::getExitFlagStatus() const
{
    return exitFlag;
}

bool GameMechs::getLoseFlagStatus() const
{
    return loseFlag;
}
    

char GameMechs::getInput() const
{
    if (MacUILib_hasChar()){
        input = MacUILib_getChar();
    }
    return input;
}

int GameMechs::getScore() const
{
    return score;
}

void GameMechs::incrementScore()
{
    score++;
}

int GameMechs::getBoardSizeX() const
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY() const
{
    return boardSizeY;
}


void GameMechs::setExitTrue()
{
    exitFlag = true;
}

void GameMechs::setLoseFlag()
{
    loseFlag = true;
}

void GameMechs::setInput(char this_input)
{
    input = this_input;
}

void GameMechs::clearInput()
{
    input = ' ';
}

// More methods should be added here