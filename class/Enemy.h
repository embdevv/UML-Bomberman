#ifndef ENEMY_H
#define ENEMY_H

#include "Player.h"

class Enemy : public Player {
private:
    int speed;
public:
    Enemy(string n, int hp, int dmg, int spd) : Player(n, hp, dmg), speed(spd) {}
    int getSpeed() { return speed; }
    void move() { cout << getName() << " moves..." << endl; } // TODO: implement map movement
};

#endif // ENEMY_H
