#ifndef BOMBERMAN_H
#define BOMBERMAN_H

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Map;
class Bomb;

#define INITIAL_BOMB_COUNT 4

class Bomberman {
private:
    int x, y;
    int bombs;
    string name;

public:
    Bomberman(string n="Bomberman") : name(n), bombs(INITIAL_BOMB_COUNT), x(4), y(3) {}

    int getX() const { return x; }
    int getY() const { return y; }
    int getBombs() const { return bombs; }

    void move(Map &map, char dir);
    void placeBomb(Map &map, vector<Bomb> &bombsVec);
};

#include "Map.h"
#include "Bomb.h"

inline void Bomberman::move(Map &map, char dir){
    int newX = x, newY = y;
    switch(dir){
        case 'w': newX--; break;
        case 's': newX++; break;
        case 'a': newY--; break;
        case 'd': newY++; break;
        default: return;
    }
    if(map.getTile(newX,newY) == ' '){
        map.setTile(x,y,' ');
        x = newX; y = newY;
        map.setTile(x,y,'P');
    }
}

inline void Bomberman::placeBomb(Map &map, vector<Bomb> &bombsVec){
    if(bombs>0){
        bombs--;
        map.setTile(x,y,'*');
        bombsVec.push_back(Bomb(x,y));
        cout << name << " placed a bomb!\n";
    } else {
        cout << name << " has no bombs left!\n";
    }
}

#endif
