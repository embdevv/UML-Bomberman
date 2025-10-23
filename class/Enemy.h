#ifndef ENEMY_H
#define ENEMY_H

/**
 * @file Enemy.h
 * @brief Class representing an enemy in the Bomberman game.
 * @details Inherits from Player and adds movement and position on the map.
 *          This class encapsulates enemy behavior including random movement and damage handling.
 */

#include <iostream>
#include <string>
#include <cstdlib>  // For rand()
#include "Map.h"
#include "Player.h"
using namespace std;

/**
 * @class Enemy
 * @brief Represents an enemy character on the map.
 */

class Enemy : public Player {
protected:
    int x, y;           ///< Current position on the map
    int moveDistance;   ///< Distance enemy can move per turn
    char symbol;        ///< Symbol representing the enemy on the map

public:
    /**
     * @brief Constructor to initialize an enemy
     * @param n Name of the enemy
     * @param hp Initial health points
     * @param dmg Damage points
     * @param startX Starting X position on the map
     * @param startY Starting Y position on the map
     * @param moveDist Distance enemy can move per turn
     * @param sym Symbol representing the enemy on the map
     * @pre hp >= 0, moveDist > 0
     * @post Enemy initialized with specified attributes
     */
    
    Enemy(string n, int hp, int dmg, int startX, int startY, int moveDist = 1, char sym = 'E')
        : Player(n, hp, dmg), x(startX), y(startY), moveDistance(moveDist), symbol(sym) {}

    virtual ~Enemy() {}  ///< Virtual destructor 

    int getX() const { return x; }      ///< Getter for X position
    int getY() const { return y; }      ///< Getter for Y position

    /**
     * @brief Get the symbol representing the enemy
     * @return Character symbol of the enemy
     */
    virtual char getSymbol() const { return symbol; }  

    /**
     * @brief Move enemy randomly on the map
     * @param map Reference to the game map
     * @post Enemy position updated if move is valid
     */
    virtual void moveRandom(Map& map) {
        int dx[4] = {-moveDistance, moveDistance, 0, 0};
        int dy[4] = {0, 0, -moveDistance, moveDistance};
        int dir = rand() % 4;
        int nx = x + dx[dir], ny = y + dy[dir];

        // Check if new position is valid
        if (map.isValidMove(nx, ny)) {
            map.setTile(x, y, ' ');  // Clear old position
            x = nx; y = ny;
            map.setTile(x, y, getSymbol());  // Set new position
        }
    }

    /**
     * @brief Reduce HP by a specified amount
     * @param dmg Amount of damage to take
     * @post HP reduced by dmg; minimum HP is 0
     */
    virtual void takeDamage(int dmg) override {
        Player::takeDamage(dmg);
        if (hp <= 0) {
            cout << name << " defeated!" << endl;
        }
    }
};

/**
 * @class Leaper
 * @brief Represents a Leaper enemy that moves 2 tiles per turn.
 */
class Leaper : public Enemy {
public:
    Leaper(int startX, int startY) : Enemy("Leaper", 2, 1, startX, startY, 2, 'L') {}
    // Inherits moveRandom, but symbol is 'L'
};

/**
 * @class Brawler
 * @brief Represents a Brawler enemy that moves 1 tile per turn.
 */
class Brawler : public Enemy {
public:
    Brawler(int startX, int startY) : Enemy("Brawler", 4, 3, startX, startY, 1, 'B') {}
    // Inherits moveRandom, but symbol is 'B'
};

#endif