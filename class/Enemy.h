#ifndef ENEMY_H
#define ENEMY_H

#include <iostream>
#include <string>
#include "Map.h"
using namespace std;

class Enemy {
private:
    int x, y;
    string name;
public:
    Enemy(string n, int startX, int startY) : name(n), x(startX), y(startY) {}
    int getX() const { return x; }
    int getY() const { return y; }

    void moveRandom(Map &map) {
        int dx[4] = {-1,1,0,0};
        int dy[4] = {0,0,-1,1};
        int dir = rand()%4;
        int nx = x+dx[dir], ny=y+dy[dir];
        if(map.getTile(nx,ny) == ' '){
            map.setTile(x,y,' ');
            x = nx; y = ny;
            map.setTile(x,y,'E');
        }
    }
};

#endif
