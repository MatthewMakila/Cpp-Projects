/*****************************************
** File:    Fruit.h
** Project: Project 4: Stardew Valley
** Author:  Matthew Makila
** Date:    4/5/21
** Section: 10/13
** E-mail:  mmakila1@umbc.edu
**
** This header file describes the behavior of the Fruit class (parent AgItem).
 * The fruit class is aggregated from the tree class. It cannot exist without a
 * tree but does not inherit from anything else. It has a color.
***********************************************/
#ifndef FRUIT_H
#define FRUIT_H
#include <string>
using namespace std;

class Fruit {
public:
    
  // Name: Fruit
  // Desc: Creates a fruit with a color
  // Preconditions:  None
  // Postconditions: A fruit is created that is red (cannot access the color anyway)
  Fruit();
    
private:
  string m_color;
};

#endif
