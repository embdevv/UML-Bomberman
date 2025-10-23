#ifndef BOMBERMAN_H
#define BOMBERMAN_H

#include "Map.h"
#include "Bomb.h"
#include "Player.h"
#include <vector>
#include <iostream>
using namespace std;

class Bomberman : public Player {
private:
    int bombs;
    int x, y;  // current position

public:
    Bomberman(string n, int _hp, int _dmg, int _bombs, int startX = 4, int startY = 4)
        : Player(n, _hp, _dmg), bombs(_bombs), x(startX), y(startY) {}

    int getX() const { return x; }
    int getY() const { return y; }
    int getBombs() const { return bombs; }

    void move(Map& map, char dir) {
        int newX = x, newY = y;
        if (dir == 'w') newX--;
        else if (dir == 's') newX++;
        else if (dir == 'a') newY--;
        else if (dir == 'd') newY++;
        if (map.isValidMove(newX, newY)) {
            map.setTile(x, y, ' ');
            x = newX; y = newY;
            map.setTile(x, y, 'P');
        }
    }

    void placeBomb(Map& map, vector<Bomb>& bombsVec) {
        if (bombs > 0) {
            bombs--;
            bombsVec.push_back(Bomb(x, y));
            cout << name << " placed a bomb!" << endl;
        } else {
            cout << name << " has no bombs left!" << endl;
        }
    }

    void displayInfo() const override {
        cout << name << " | HP: " << hp << " | DMG: " << dmg << " | Bombs: " << bombs << endl;
    }
};

#endif