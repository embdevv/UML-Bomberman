#ifndef BOMBERMAN_H
#define BOMBERMAN_H

/**
 * @file Bomberman.h
 * @brief Class representing the Bomberman player.
 * @details Inherits from Player and adds bomb management and movement on the map.
 * This class encapsulates the player's movement, bomb placement, and player-specific attributes.
 */

#include "Map.h"
#include "Bomb.h"
#include "Player.h"
#include <vector>
#include <iostream>
using namespace std;

/**
 * @class Bomberman
 * @brief Represents the Bomberman player character controlled by the user.
 */
class Bomberman : public Player {
private:
    int bombs;  ///< Number of bombs available
    int x, y;   ///< Current position on the map

public:
    /**
     * @brief Constructor to initialize Bomberman player
     * @param n Name of the player
     * @param _hp Initial health points
     * @param _dmg Damage points
     * @param _bombs Initial number of bombs
     * @param startX Starting X position on the map
     * @param startY Starting Y position on the map
     * @pre _hp >= 0, _bombs >= 0
     * @post Bomberman initialized with specified attributes
    */
    Bomberman(string n, int _hp, int _dmg, int _bombs, int startX = 4, int startY = 4)
        : Player(n, _hp, _dmg), bombs(_bombs), x(startX), y(startY) {}

    int getX() const { return x; }          ///< Getter for X position
    int getY() const { return y; }          ///< Getter for Y position
    int getBombs() const { return bombs; }  ///< Getter for number of bombs

    /**
     * @brief Move Bomberman on the map based on input direction
     * @param map Reference to the game map
     * @param dir Direction character ('w', 'a', 's', 'd')
     * @post Bomberman's position updated if move is valid
     */
    void move(Map& map, char dir) {
        int newX = x, newY = y;
        if (dir == 'w') newX--;
        else if (dir == 's') newX++;
        else if (dir == 'a') newY--;
        else if (dir == 'd') newY++;
        
        // Check if new position is valid
        if (map.isValidMove(newX, newY)) {
            map.setTile(x, y, ' '); // Clear the old position
            x = newX; y = newY;
            map.setTile(x, y, 'P'); // Set new position
        }
    }

    /**
     * @brief Place a bomb on current position
     * @param map Reference to the game map
     * @param bombsVec Reference to the vector of active bombs
     * @pre bombs > 0
     * @post Adds a new bomb to bombsVec and decreases bomb count
     */
    void placeBomb(Map& map, vector<Bomb>& bombsVec) {
        if (bombs > 0) {
            bombs--;
            bombsVec.push_back(Bomb(x, y));
            cout << name << " placed a bomb!" << endl;
        } else {
            cout << name << " has no bombs left!" << endl;
        }
    }

    /** 
     * @brief Display Bomberman information
     * @post Prints Bomberman's name, HP, damage, and remaining bombs to console
     */

    void displayInfo() const override {
        cout << name << " | HP: " << hp << " | DMG: " << dmg << " | Bombs: " << bombs << endl;
    }
};

#endif