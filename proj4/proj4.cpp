/*****************************************
** File:    proj4.cpp
** Project: Project 4: Stardew Valley
** Author:  Matthew Makila
** Date:    4/5/21
** Section: 10/13
** E-mail:  mmakila1@umbc.edu
**
** This file is the main driver for project 4. This simply creates a farm
 * and begins the simulation.
***********************************************/
#include <iostream>
#include <string>
using namespace std;

#include "Farm.h"

int main () {
  Farm farm;
  farm.StartSimulation();
  return 0;
}
