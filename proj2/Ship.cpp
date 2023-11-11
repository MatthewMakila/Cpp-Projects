/*****************************************
** File:    Ship.cpp
** Project: Project 2: No Man's Alchemy
** Author:  Matthew Makila
** Date:    3/9/21
** Section: 10/13
** E-mail:  mmakila1@umbc.edu
**
** This file includes the methods to create a ship object and
 * set its name as given by the user. The accessors and mutators
 * are called several times in name to retrieve and alter the ship's name,
 * its materials, and its rank.
***********************************************/

#include "Ship.h"

// Name: Ship() - Default Constructor
// Desc: Used to build a new Player Ship
// Preconditions - Requires default values
// Post-conditions - Creates a new Player Ship
Ship::Ship(){ // default
    SetName("Ship");
}

// Name: Ship(name) - Overloaded constructor
// Desc - Used to build a new Player Ship
// Preconditions - Requires name
// Post-conditions - Creates a new Player Ship
Ship::Ship(string name){ // overloaded
    SetName(name);
}

// Name: GetName()
// Desc - Getter for the Player Ship's name
// Preconditions - Player Ship exists
// Post-conditions - Returns the name of the Player Ship
string Ship::GetName(){
    return m_shipName;
}

// Name: SetName(string)
// Desc - Allows the user to change the name of the Player Ship
// Preconditions - Player Ship exists
// Post-conditions - Sets name of Player Ship
void Ship::SetName(string name){
    m_shipName = name;
}

// Name: CheckMaterial(Material)
// Desc - Checks to see if the Ship has a material
// Preconditions - Ship already has materials
// Post-conditions - Returns index of material if the Ship has it else -1
int Ship::CheckMaterial(Material m1){
    for (int i = 0; i < PROJ2_SIZE; i++){
        // if the material name matches a material in the ship and the ship has at least 1 of it, return its index
        if (m_myMaterials[i].m_name == m1.m_name && m_myMaterials[i].m_quantity > 0){
           return i;
        }
    }
    return -1;
}

// Name: AddMaterial(string)
// Desc - Inserts a material into the Ship's list of materials
// Preconditions - Ship exists
// Post-conditions - Add a material to the Ship's m_myMaterials with a quantity of 0
void Ship::AddMaterial(Material m1){
    m_myMaterials[m_numMaterials] = m1;
    m_numMaterials += 1;

}

// Name: IncrementQuantity(Material)
// Desc - Adds quantity to list of materials the Ship knows
// Preconditions - Ship exists
// Post-conditions - Increases quantity of material for the Ship
void Ship::IncrementQuantity(Material m1){
    // loop through and see if the material passed through matches the material in ship's list. Update it then
    for (int i = 0; i < PROJ2_SIZE; i++){
        if (m_myMaterials[i].m_name == m1.m_name){
            m_myMaterials[i].m_quantity += 1;
        }
    }
}

// Name: DecrementQuantity(Material)
// Desc - Reduces quantity from the Ship's inventory with true, if no quantity false
// Preconditions - A Ship exists
// Post-conditions - Reduces quantity of material for the Ship
bool Ship::DecrementQuantity(Material m1) {
    if (m1.m_quantity > 0) {
        // returns true for decreasing material amount if there is at least 1 of the material
        for (int i = 0; i < PROJ2_SIZE; i++) {
            if (m_myMaterials[i].m_name == m1.m_name) {
                m_myMaterials[i].m_quantity -= 1;
                return true;
            }
        }
    }
    return false;
}

// Name: CheckQuantity(Material)
// Desc - Checks to see if quantity of two merge materials are available
// Preconditions - Ship exists with materials
// Post-conditions - Returns true if both are available (including two of same material)
bool Ship::CheckQuantity(Material m1, Material m2){
    // if the quantities of both materials are at least 1, there is enough of each to merge
    if (m1.m_quantity > 0 && m2.m_quantity > 0){
        return true;
    // if both items are the same, make sure there is at least 2 of that material to merge
    } else if ((m1.m_name == m2.m_name) && m1.m_quantity > 1){
        return true;
    // return false if there aren't at least 1 of each material requested
    } else {
        return false;
    }
}

// Name: GetMaterial(int)
// Desc - Checks to see if the Ship has any materials
// Preconditions - The Ship already has materials
// Post-conditions - Returns material at specific index
Material Ship::GetMaterial(int materialIndex){
    return m_myMaterials[materialIndex];
}

// Name: IncRank()
// Desc - Increments the rank of the ship to the next rank.
// Preconditions - Ship exists and has a rank
// Post-conditions - m_shipRank will move to the next character
void Ship::IncRank(){
    char temp = m_shipRank;
    for (int i = 0; i < RANK_SIZE; i++){
        if (m_shipRank == RANKS[i]){
            temp = RANKS[i + 1];
        }
    }
    m_shipRank = temp;
}

// Name: GetRank()
// Desc - Checks to see what the current ship's rank is
// Preconditions - The ship exists
// Post-conditions - Returns the character indicating the rank of the ship
char Ship::GetRank(){
    // return a rank of the ship if it matches one of the possible ranks, otherwise if not found return starter rank
    char starterRank = RANKS[0];
    for (int i = 0; i < RANK_SIZE; i++){
        if (m_shipRank == RANKS[i]){
            m_shipRank = RANKS[i];
            return m_shipRank;
        }
    }
    m_shipRank = starterRank;
    return starterRank;
}