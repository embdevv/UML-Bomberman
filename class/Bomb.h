#ifndef BOMB_H
#define BOMB_H

#include <iostream>
using namespace std;

class Bomb {
private:
    int x, y;       // position
    int timer;      // countdown before explosion
    int power;      // explosion range
    bool exploded;  // has it exploded

public:
    Bomb(int xPos, int yPos, int t = 3, int p = 1) {
        x = xPos; y = yPos;
        timer = t; power = p;
        exploded = false;
    }

    int getX() const { return x; }
    int getY() const { return y; }
    bool hasExploded() const { return exploded; }

    void tick() {
        if(timer > 0) timer--;
        if(timer == 0) exploded = true;
    }
};

#endif
