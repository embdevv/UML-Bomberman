#ifndef BOMBERMAN_H
#define BOMBERMAN_H

#include "Map.h"
#include "Bomb.h"
#include "Player.h"

#include <vector>
#include <iostream>
using namespace std;

class Bomberman {
private:
    string name;
    int hp, dmg;
    int bombs;
    int x, y; // current position

public:
    Bomberman(string n, int _hp, int _dmg, int _bombs, int startX = 1, int startY = 1)
        : name(n), hp(_hp), dmg(_dmg), bombs(_bombs), x(startX), y(startY) {}

    int getX() const { return x; }
    int getY() const { return y; }
    int getHp() const { return hp; }
    int getDamage() const { return dmg; }
    int getBombs() const { return bombs; }

    void move(Map &map, char dir) {
        int newX = x, newY = y;
        switch(dir){
            case 'w': newX--; break;
            case 's': newX++; break;
            case 'a': newY--; break;
            case 'd': newY++; break;
            default: return;
        }
        if (map.getTile(newX,newY) == ' ') {
            map.setTile(x,y,' '); // clear old
            x=newX; y=newY;
            map.setTile(x,y,'P'); // move player
        }
    }

    void placeBomb(Map &map, vector<Bomb> &bombsVec) {
    if (bombs > 0) {
        bombs--;
        bombsVec.push_back(Bomb(x, y, 4, 1)); // timer = 3
        cout << name << " placed a bomb!" << endl;
    } else {
        cout << name << " has no bombs left!" << endl;
    }
    }

    string getName() const { return name; }

    void displayInfo() const {
        cout << name << " | HP: " << hp << " | DMG: " << dmg << " | Bombs: " << bombs << endl;
    }
};

#endif
