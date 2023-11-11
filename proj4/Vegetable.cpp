/*****************************************
** File:    Vegetable.cpp
** Project: Project 4: Stardew Valley
** Author:  Matthew Makila
** Date:    4/5/21
** Section: 10/13
** E-mail:  mmakila1@umbc.edu
**
** This file implements the methods from the vegetable class. The veggie is constructed
 * through its inheritance from AgItem and then has its own version of Tick and harvest
 * implemented. It has its own overloaded operator to print an object of its type
***********************************************/

#include "Vegetable.h"

// Name: Vegetable (Default constructor)
// Desc: Creates a vegetable with size 0
// Preconditions:  Uses AgItem default constructor
// Postconditions: A vegetable is created.
Vegetable::Vegetable(): AgItem(){} // size 0 by default

// Name: Harvest
// Desc: If the vegetable is harvestable (fully mature), returns size to increase farm's food
// Preconditions:  IsHarvestable
// Postconditions: Returns integer size of vegetable for food
int Vegetable::Harvest(){
    // return the 1 per size food when determined to be harvestable
    return GetSize();

}

// Name: Tick
// Desc: A season passes in the vegetable's life if they are fully mature, IsHarvestable flipped
// Preconditions:  If the size is less than the maximum vegetable size, increases size
// Postconditions: Vegetable either grows or becomes harvestable
// Assume that a vegetable is always fed.
void Vegetable::Tick(bool isMaxSize){

    if (GetSize() == MAX_VEG_SIZE){
        // make it harvestable when it's max size (2)
        isMaxSize = true;
        SetIsHarvestable(isMaxSize);
    } else {
        // upgrade its size
        SetSize(GetSize() + 1);
    }
}

// Name: GetType
// Desc: Returns the name of the subtype (Vegetable)
// Preconditions:  None
// Postconditions: Returns string name of the subtype (Vegetable)
string Vegetable::GetType(){
    // return subtype
    const string TYPE_V = "Vegetable";
    return TYPE_V;
}

// Name: overloaded operator<<
// Desc: Allows Vegetable objects to be outputted
// Preconditions:  None
// Postconditions: Returns output stream with this format
//                 Vegetable | Not Harvestable | Seedling
ostream& Vegetable::operator<<(ostream& VeggieOut){
    string harvestable;
    const string HARVESTABLE = "Harvestable";
    const string NOT_HARVEST = "Not Harvestable";
    // check if vegetable is harvestable
    if (!GetIsHarvestable()){
        harvestable = NOT_HARVEST;
    } else {
        harvestable = HARVESTABLE;
    }
    // output vegetable object
    VeggieOut << GetType() << CONCAT << harvestable << CONCAT << Veg_Size[GetSize()];
    return VeggieOut;
}

