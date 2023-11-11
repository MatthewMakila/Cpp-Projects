/*****************************************
** File:    Fruit.cpp
** Project: Project 4: Stardew Valley
** Author:  Matthew Makila
** Date:    4/5/21
** Section: 10/13
** E-mail:  mmakila1@umbc.edu
**
** This file describes the implementation of the Fruit class.
 * The fruit class is aggregated from the tree class. It has a constructor
 * to initialize its color.
***********************************************/
#include "Fruit.h"
const string COLOR = "red";

// Name: Fruit
// Desc: Creates a fruit with a color
// Preconditions:  None
// Postconditions: A fruit is created that is red (cannot access the color anyway)
Fruit::Fruit(){
    m_color = COLOR;
}