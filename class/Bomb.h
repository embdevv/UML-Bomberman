#ifndef BOMB_H
#define BOMB_H

#include <iostream>
using namespace std;

/**
 * @file Bomb.h
 * @brief Class representing a bomb in the Bomberman game.
 * @details Contains attributes for position, timer, and power.
 * Provides functionality to tick down the timer and check for explosion.
 * 
 * References:
 * - GDPROG3 Course Materials
 * 
 * 
 * @class Bomb
 * @brief Represents a bomb placed on the map.
 */

class Bomb {
private:
    int x, y;     ///< Position on map
    int timer;    ///< Ticks until explosion
    int power;    ///< Explosion range

public:
    Bomb(int _x, int _y, int _timer = 3, int _power = 1)
        : x(_x), y(_y), timer(_timer), power(_power) {}

    void tick() { if (timer > 0) timer--; }         ///< Decrease timer by 1

    bool hasExploded() const { return timer == 0; } ///< Check if bomb has exploded

    int getTimer() const { return timer; }          ///< Get remaining timer
    int getX() const { return x; }                  ///< Get X position
    int getY() const { return y; }                  ///< Get Y position
    int getPower() const { return power; }          ///< Get explosion power
};

#endif