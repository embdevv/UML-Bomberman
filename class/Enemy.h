#ifndef ENEMY_H
#define ENEMY_H

#include <iostream>
#include <string>
#include <cstdlib>  // For rand()
#include "Map.h"
#include "Player.h"
using namespace std;

class Enemy : public Player {
protected:
    int x, y;
    int moveDistance;
    char symbol;  // New: Symbol for map display

public:
    Enemy(string n, int hp, int dmg, int startX, int startY, int moveDist = 1, char sym = 'E')
        : Player(n, hp, dmg), x(startX), y(startY), moveDistance(moveDist), symbol(sym) {}

    virtual ~Enemy() {}  // Virtual for subclasses

    int getX() const { return x; }
    int getY() const { return y; }

    virtual char getSymbol() const { return symbol; }  // Virtual for subclasses to override

    virtual void moveRandom(Map& map) {
        int dx[4] = {-moveDistance, moveDistance, 0, 0};
        int dy[4] = {0, 0, -moveDistance, moveDistance};
        int dir = rand() % 4;
        int nx = x + dx[dir], ny = y + dy[dir];
        if (map.isValidMove(nx, ny)) {
            map.setTile(x, y, ' ');  // Clear old position
            x = nx; y = ny;
            map.setTile(x, y, getSymbol());  // Use symbol instead of 'E'
        }
    }

    virtual void takeDamage(int dmg) override {
        Player::takeDamage(dmg);
        if (hp <= 0) {
            cout << name << " defeated!" << endl;
        }
    }
};

// Subclass for Leaper: Moves 2 tiles, symbol 'L'
class Leaper : public Enemy {
public:
    Leaper(int startX, int startY) : Enemy("Leaper", 2, 1, startX, startY, 2, 'L') {}
    // Inherits moveRandom, but symbol is 'L'
};

// Subclass for Brawler: Moves 1 tile, higher HP/damage, symbol 'B' (renamed from Tank)
class Brawler : public Enemy {
public:
    Brawler(int startX, int startY) : Enemy("Brawler", 4, 3, startX, startY, 1, 'B') {}
    // Inherits moveRandom, but symbol is 'B'
};

#endif