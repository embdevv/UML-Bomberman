#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <iostream>
using namespace std;

/**
 * Base Player class represents both hero and enemies.
 */
class Player {
protected:
    string name;
    int hp;
    int dmg;

public:
    Player(string n, int health, int damage) : name(n), hp(health), dmg(damage) {}
    virtual ~Player() {}  // Virtual destructor for polymorphism

    string getName() const { return name; }
    int getHp() const { return hp; }
    int getDamage() const { return dmg; }

    void setHp(int value) { hp = value; }
    void setDamage(int value) { dmg = value; }

    /**
     * Reduce HP when taking damage (virtual for subclasses)
     */
    virtual void takeDamage(int amount) {
        hp -= amount;
        if (hp < 0) hp = 0;
    }

    /**
     * Display player info (virtual for polymorphism)
     */
    virtual void displayInfo() const {
        cout << "------------\n";
        cout << name << "\nHP: " << hp << " DMG: " << dmg << "\n------------\n";
    }
};

#endif