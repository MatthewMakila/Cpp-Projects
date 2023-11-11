/*****************************************
** File:    proj2.cpp
** Project: Project 2: No Man's Alchemy
** Author:  Matthew Makila
** Date:    3/9/21
** Section: 10/13
** E-mail:  mmakila1@umbc.edu
**
** This file is the main driver for project 2. It begins
 * a new game by creating a game object and starts the game using the
 * startGame method.
***********************************************/

#include "Game.h"

#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
using namespace std;

int main () {
    srand(time(NULL));
    Game newGame;
    newGame.StartGame();
    return 0;
}