/*****************************************
** File:    Tree.cpp
** Project: Project 4: Stardew Valley
** Author:  Matthew Makila
** Date:    4/5/21
** Section: 10/13
** E-mail:  mmakila1@umbc.edu
**
** This file implements the methods from the Tree class. A Tree is constructed
 * through its inheritance from AgItem and then has its own version of Tick and harvest
 * implemented (it harvests fruit and only the tree after age 60).
 * It has its own overloaded operator to print an object of its type.
***********************************************/

#include "Tree.h"

// Name: Tree (Default constructor)
// Desc: Creates a tree with size 0 and age of 0
// Preconditions:  Uses AgItem default constructor
// Postconditions: A tree is created.
Tree::Tree(): AgItem(){
    m_age = 0;
}

// Name: ~Tree
// Desc: Destructor for tree (and importantly fruit)
// Preconditions:  Tree exists
// Postconditions: All fruit is purged from tree.
Tree::~Tree(){
    // delete newly allocated fruit
    for (unsigned int i = 0; i < m_fruit.size(); i++){
        delete m_fruit.at(i);
    }
}

// Name: Tick
// Desc: A season passes is the tree's life (always fed)
// Preconditions: Tree exists
// Postconditions: Returns amount of fruit harvested each season.
// One of the following occurs:
//    1. Tree is not Mature yet and ages. Every 4 seasons, size increases til age 12 when fruits
//    2. Tree is Mature and grows a one fruit a season. Fruit is harvested every season.
//    3. Tree is 60 seasons old and is cut down (IsHarvesteable)
void Tree::Tick(bool IsHarvestable){
    // 3 branches: increase size if not mature (age = 12), add more fruit if mature, cut tree down if age = 60
    if (m_age <= SEASONS_TO_FRUIT){
        // if enough seasons to pass to size up, move tree to next phase of size
        if ((m_age % SEASONS_TO_SIZE) == 0 && (m_age < SEASONS_TO_FRUIT)){
            SetSize(GetSize() + 1);
        }
        // add to age
        m_age += 1;

    }
    else if (m_age > SEASONS_TO_FRUIT){
        // if > 12 seasons old, keep making a new fruit and make it harvestable
        m_age += 1;
        IsHarvestable = true;
        SetIsHarvestable(IsHarvestable);
        Fruit* newFruit = new Fruit();
        m_fruit.push_back(newFruit);
    }

}

// Name: Harvest
// Desc: If there is fruit, removes last fruit and returns 1. If 60 seasons old, returns 0
// Preconditions:  Tree exists
// Postconditions: Fruit is returned(1 farm food) or dead tree (0 worth and 0 farm food)
int Tree::Harvest(){
    // erase and delete fruit once collected?
    for (unsigned int i = 0; i < m_fruit.size(); i++){
        delete m_fruit.at(i);
        m_fruit.erase(m_fruit.begin()+i);
    }
    // if tree 60, no food or worth
    if (m_age > SEASONS_TO_HARVEST){
        return 0;
    } else {
        // return 1 food for the fruit collected
        return 1;
    }


}

// Name: GetType
// Desc: Returns the name of the subtype (Tree)
// Preconditions:  None
// Postconditions: Returns string name of the subtype (Tree)
string Tree::GetType(){
    const string TYPE_T = "Tree";
    return TYPE_T;
}

// Name: overloaded operator<<
// Desc: Allows Tree objects to be outputted
// Preconditions:  None
// Postconditions: Returns output stream with this format:
//                 Tree  | Seedling | Not Harvestable | Not Fruiting | Fruit Count: 0

ostream& Tree::operator<<(ostream& TreeOut){
    string harvestable;
    string fruiting;
    const string HARVESTABLE = "Harvestable";
    const string NOT_HARVEST = "Not Harvestable";
    const string FRUITING = "Fruiting";
    const string NOT_FRUITING = "Not Fruiting";

    if (m_age < SEASONS_TO_HARVEST){
        harvestable = NOT_HARVEST;
    } else {
        harvestable = HARVESTABLE;
    }

    /***
     * CHECK OUT TERNARY OPERATOR FOR THE HARVESTABLE AND FRUITING OUTPUT IN THE COUT!!!!
     */

    if (m_age > SEASONS_TO_FRUIT) {
        fruiting = FRUITING;
    } else {
        fruiting = NOT_FRUITING;
    }

    // output the Tree object with data
    TreeOut << GetType() << CONCAT << TREE_SIZE[GetSize()] << CONCAT << harvestable << CONCAT << fruiting
              << CONCAT << " Fruit Count: " << m_fruit.size();
    return TreeOut;
}
