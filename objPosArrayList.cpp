#include "objPosArrayList.h"

// Paste your Tested implementation here.
// Paste your Tested implementation here.
// Paste your Tested implementation here.

//yeah okay


//construct
objPosArrayList::objPosArrayList(){
    aList = new objPos[ARRAY_MAX_CAP]; //give mem to array

    listSize = 0; //empty beginning

    arrayCapacity = ARRAY_MAX_CAP; //sets max cap <3
}


//destructa
objPosArrayList::~objPosArrayList(){
    delete[] aList; //goodbye meemory

}

//get current listsize
int objPosArrayList::getSize() const{
    return listSize;
}

//to place an objPos at the list's head (snek)
void objPosArrayList::insertHead(objPos thisPos){
    if(listSize >= arrayCapacity){
        return; //stops overflow
    }

    //shift stuff right i think to make room for snek head
    for(int i = listSize; i > 0; i--){
        aList[i] = aList[i-1];
    }

    aList[0] = thisPos; //new element @head
    ++listSize;
}

//objpos at tail (snek tail)
void objPosArrayList::insertTail(objPos thisPos){
    if(listSize >= arrayCapacity){
        return; //stops overflow
    }
    aList[listSize] = thisPos; //place element at the end
    ++listSize;
}

//remove head object:
void objPosArrayList::removeHead(){
    if(listSize==0){
        return; //nothing 2 even remove
    }

    //shift stuff left to fill empty space
    for (int i  = 0; i < listSize -1; i++){
        aList[i] = aList[i+1];
    }
    --listSize; //decrease.
}


//remove tail object
void objPosArrayList::removeTail(){
    if(listSize == 0){
        return; //nothing to remove
    }
    aList[listSize - 1] = objPos();
    --listSize; //just decrease the size of the list hehe
}

//get element at list head:
objPos objPosArrayList::getHeadElement() const{
    if(listSize == 0){
        return objPos(); //give back a default objpos if the list is emptu
    }
    return aList[0]; //returns element at first index
}

//get element at list tail
objPos objPosArrayList::getTailElement() const{
    if(listSize == 0){
        return objPos(); //give back a default objpos if the list is emptu
    }

    return aList[listSize -1]; //returns the thing at the end of the list
}

//get element at some index (specific)
objPos objPosArrayList::getElement(int index) const{
    if(index < 0|| index >= listSize){
        return objPos(); //return default if index is not valid
    }
    return aList[index]; //return at the given index otherwise
}