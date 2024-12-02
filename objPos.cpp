#include "objPos.h"
#include <utility> //for std::move...

objPos::objPos()
{
    pos = new Pos;
    pos->x = 0;
    pos->y = 0;
    symbol = 0; //NULL
}

objPos::objPos(int xPos, int yPos, char sym)
{
    pos = new Pos;
    pos->x = xPos;
    pos->y = yPos;
    symbol = sym;
}

// Respect the rule of six / minimum four
// [TODO] Implement the missing special member functions to meet the minimum four rule

//missing copy, copy assignment, move, move assigmen, destructor. adding those here. - leah

//copy constructor
objPos::objPos(const objPos& other) 
{
    pos = new Pos;  // Allocate new memory for pos
    pos->x = other.pos->x;
    pos->y = other.pos->y;
    symbol = other.symbol;
}

//copy assignment operator:
objPos& objPos::operator=(const objPos& other){
    if (this == &other){
        return *this;
    }
    
//delete existing mem
    delete pos;

    //new mem and copy
    pos = new Pos;
    pos->x =  other.pos->x;
    pos->y =  other.pos->y;
    symbol = other.symbol;

    return *this;
}

//move constructor
objPos::objPos(objPos&& other) noexcept{
    pos = other.pos;
    symbol = other.symbol;
    other.pos = nullptr; //nulls source to avoid stupid things
}


//move assignment operator

objPos& objPos::operator=(objPos&& other) noexcept{
    if (this == &other)
        return *this;

    delete pos;
    pos = other.pos;
    symbol = other.symbol;

    other.pos = nullptr;
    return *this;
}


//destructor
objPos::~objPos(){
    delete pos; //be free
}




void objPos::setObjPos(objPos o)
{
    pos->x = o.pos->x;
    pos->y = o.pos->y;
    symbol = o.symbol;
}

void objPos::setObjPos(int xPos, int yPos, char sym)
{
    pos->x = xPos;
    pos->y = yPos;
    symbol = sym;
}

objPos objPos::getObjPos() const
{
    objPos returnPos;
    returnPos.pos->x = pos->x;
    returnPos.pos->y = pos->y;
    returnPos.symbol = symbol;
    
    return returnPos;
}

char objPos::getSymbol() const
{
    return symbol;
}

bool objPos::isPosEqual(const objPos* refPos) const
{
    return (refPos->pos->x == pos->x && refPos->pos->y == pos->y);
}

char objPos::getSymbolIfPosEqual(const objPos* refPos) const
{
    if(isPosEqual(refPos))
        return symbol;
    else
        return 0;
}
