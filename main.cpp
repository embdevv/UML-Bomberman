/**
 * Author: Erica Mauriz Barundia
 * Initial Date: 2024-10-13 | Last Updated: 2024-10-23
 * For GDPROG3 MCO1 - Bomberman Project
*/

/** 
 * @file main.cpp
 * @brief Entry point for the Bomberman game.
 * @details Initializes and starts the game loop.
 * This program initializes the Bomberman player and enemy objects, 
 * places them on the map, and demonstrates basic movement and bomb mechanics.
 * It is designed according to internal documentation and coding standards.
 */

#include "class/Game.h"
#include <iostream>
using namespace std;

int main() {
    
    Game game;
    game.run();
    return 0;
}