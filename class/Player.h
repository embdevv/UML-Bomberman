#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <iostream>
using namespace std;

/**
 * @file Player.h
 * @brief Base class representing a player entity in the Bomberman game. 
 * @details Contains basic attributes like name, HP, and damage. 
 * Provides common functionality like taking damage and displaying information.
    
    References: 
    * - GDPROG3 Course Materials
    * - Virtual Desctructors in C++: https://www.geeksforgeeks.org/cpp/when-to-use-virtual-destructors-in-cpp/
    * 

 */

 /** 
  * @class Player
  * @brief Represents a general player or enemy.
 */

class Player {
protected:
    string name; ///< Player name
    int hp;      ///< Health points
    int dmg;     ///< Damaage points

public:
    /**
     * @brief Constructor to initialize a player
     * @param n Name of player
     * @param health Initial health points
     * @param damage Damage points
     * @pre health >= 0
     * @post Player initialized with specified attributes
     */

    Player(string n, int health, int damage) : name(n), hp(health), dmg(damage) {}
    virtual ~Player() {}  ///< Virtual destructor for polymorphism

    string getName() const { return name; } ///< Getter for player name
    int getHp() const { return hp; }        ///< Getter for health points
    int getDamage() const { return dmg; }   ///< Getter for damage points

    void setHp(int value) { hp = value; }   ///< Setter for health points
    void setDamage(int value) { dmg = value; } ///< Setter for damage points

    /**
     * @brief Reduce HP by a specified amount
     * @param amount Amount of damage to take or to be subtracted
     * @post HP reduced by amount; minimum HP is 0
     */
    virtual void takeDamage(int amount) {
        hp -= amount;
        if (hp < 0) hp = 0;
    }

    /**
     * @brief Display player information
     * @post  Prints player's name, HP, and damage to console
     */
    virtual void displayInfo() const {
        cout << "------------\n";
        cout << name << "\nHP: " << hp << " DMG: " << dmg << "\n------------\n";
    }
};

#endif