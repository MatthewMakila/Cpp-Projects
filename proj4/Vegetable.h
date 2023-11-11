/*****************************************
** File:    Vegetable.h
** Project: Project 4: Stardew Valley
** Author:  Matthew Makila
** Date:    4/5/21
** Section: 10/13
** E-mail:  mmakila1@umbc.edu
**
** This header file describes the behavior of vegetable subclass (parent AgItem).
 * Information to declare the Vegetable's own Tick and harvest functions are included.
***********************************************/

#ifndef VEGETABLE_H
#define VEGETABLE_H
#include "AgItem.h"

//Constants
const string Veg_Size[] {"Seedling", "Medium", "Fully Mature"}; //Names of the sizes
const int MAX_VEG_SIZE = 2; //1 = seedling 2 = medium 3 = fully mature

class Vegetable: public AgItem {
public:
  // Name: Vegetable (Default constructor)
  // Desc: Creates a vegetable with size 0
  // Preconditions:  Uses AgItem default constructor
  // Postconditions: A vegetable is created.
  Vegetable();

  // Name: Harvest
  // Desc: If the vegetable is harvestable (fully mature), returns size to increase farm's food
  // Preconditions:  IsHarvestable
  // Postconditions: Returns integer size of vegetable for food
  virtual int Harvest();

  // Name: Tick
  // Desc: A season passes in the vegetable's life if they are fully mature, IsHarvestable flipped
  // Preconditions:  If the size is less than the maximum vegetable size, increases size
  // Postconditions: Vegetable either grows or becomes harvestable
  // Assume that a vegetable is always fed.
  virtual void Tick(bool);

  // Name: GetType
  // Desc: Returns the name of the subtype (Vegetable)
  // Preconditions:  None
  // Postconditions: Returns string name of the subtype (Vegetable)
  virtual string GetType();
  
  // Name: overloaded operator<<
  // Desc: Allows Vegetable objects to be outputted
  // Preconditions:  None
  // Postconditions: Returns output stream with this format
  //                 Vegetable | Not Harvestable | Seedling
  virtual ostream& operator<<(ostream&);

};

#endif 
