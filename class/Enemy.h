#ifndef ENEMY_H
#define ENEMY_H

#include <iostream>
#include <string>
#include <cstdlib>  // For rand()
#include "Map.h"
#include "Player.h"
using namespace std;

class Enemy : public Player {
private:
    int x, y;
    int moveDistance;  // 1 = normal, 2 = leaper

public:
    Enemy(string n, int hp, int dmg, int startX, int startY, int moveDist = 1)
        : Player(n, hp, dmg), x(startX), y(startY), moveDistance(moveDist) {}

    int getX() const { return x; }
    int getY() const { return y; }

    void moveRandom(Map& map) {
        int dx[4] = {-moveDistance, moveDistance, 0, 0};
        int dy[4] = {0, 0, -moveDistance, moveDistance};
        int dir = rand() % 4;
        int nx = x + dx[dir], ny = y + dy[dir];
        if (map.isValidMove(nx, ny)) {
            map.setTile(x, y, ' ');
            x = nx; y = ny;
            map.setTile(x, y, 'E');
        }
    }

    void takeDamage(int dmg) override {
        Player::takeDamage(dmg);
        if (hp <= 0) {
            cout << name << " defeated!" << endl;
        }
    }
};

#endif