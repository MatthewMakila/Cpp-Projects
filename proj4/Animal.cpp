/*****************************************
** File:    Animal.cpp
** Project: Project 4: Stardew Valley
** Author:  Matthew Makila
** Date:    4/5/21
** Section: 10/13
** E-mail:  mmakila1@umbc.edu
**
** This file implements the methods from the animal class. The animal is constructed
 * through its inheritance from AgItem and then has its own version of Tick and harvest
 * implemented. It has its own overloaded operator to print an object of its type
***********************************************/
#include "Animal.h"

// Name: Animal (Default constructor)
// Desc: Creates an Animal with size 0
// Preconditions:  Uses AgItem default constructor
// Postconditions: An animal (chicken) is created.
Animal::Animal(): AgItem(){
    const string NAME = "Chicken";
    m_name = NAME;
}

// Name: Tick
// Desc: A season passes is the animal's life (passed boolean if it was fed - eats "farm's food")
// Preconditions: If farm has food, animal is automatically fed
// Postconditions: One of the following occurs
//    1. Animal is fed and size increases (not max yet)
//    2. Animal is fed hits max size and is made harvestable
//    3. Animal is not fed. Size does not increase. If second no feed, is harvested (small).
void Animal::Tick(bool isFed){
    // if farm has food, animals get fed and its size increases
    bool isHarvestable;

    if (isFed){
        m_IsHungry = false;
    }
    // if animal is max size, harvest
    if (GetSize() == ANIMAL_MAX_SIZE){
        isHarvestable = true;
        SetIsHarvestable(isHarvestable);
    }
    // if not max size yet and fed, harvest it
    if (isFed && (GetSize() != ANIMAL_MAX_SIZE)) {
        SetSize(GetSize() + 1);
    }

    // check if it is not fed
    if (!isFed){
        // check if not fed second time and harvest if already hungry
        if (m_IsHungry){
            isHarvestable = true;
            SetIsHarvestable(isHarvestable);
        } else {
            m_IsHungry = true;
        }
    }
}

// Name: Harvest
// Desc: If the animal is harvestable (adult), returns worth * size to increase farm's money
// Preconditions:  IsHarvestable
// Postconditions: Animal harvested and money is gained (worth * size)
int Animal::Harvest(){
    // harvest and add dinero if the animal is adult
    int money = GetSize() * GetWorth();
    return money;
}

// Name: GetType
// Desc: Returns the name of the subtype (Animal)
// Preconditions:  None
// Postconditions: Returns string name of the subtype (Animal)
string Animal::GetType(){
    const string TYPE_A = "Animal";
    return TYPE_A;
}

// Name: overloaded operator<<
// Desc: Allows Animal objects to be outputted
// Preconditions:  None
// Postconditions: Returns output stream with this format:
//                 Animal | Chicken | Not Harvestable | Born | Fed

ostream& Animal::operator<< (ostream& animalOut){
    string harvestable;
    const string HARVESTABLE = "Harvestable";
    const string NOT_HARVEST = "Not Harvestable";
    const string HUNGRY = "Not Fed";
    const string NOT_HUNGRY = "Fed";

    // check if animal is harvestable
    if (!GetIsHarvestable()){
        harvestable = NOT_HARVEST;
    } else {
        harvestable = HARVESTABLE;
    }

    string hungry;
    // check if animal has not been fed
    if (m_IsHungry){
        hungry = HUNGRY;
    } else {
        hungry = NOT_HUNGRY;
    }
    // output the animal object
    animalOut << GetType() << CONCAT << m_name << CONCAT << harvestable << CONCAT << ANIMAL_SIZE[GetSize()]
    << CONCAT << hungry;
    return animalOut;
}