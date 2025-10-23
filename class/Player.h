#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <iostream>
using namespace std;

class Player {
protected:
    string name;
    int hp;
    int dmg;
public:
    Player(string n, int health, int damage) : name(n), hp(health), dmg(damage) {}
    string getName() { return name; }
    int getHp() { return hp; }
    int getDamage() { return dmg; }
    void setHp(int value) { hp = value; }
    void takeDamage(int amount) {
        hp -= amount;
        if(hp <= 0) {
            hp = 0;
            cout << name << " died!" << endl;
        } else {
            cout << name << " took " << amount << " damage!" << endl;
        }
    }
};

#endif
// PLAYER_H