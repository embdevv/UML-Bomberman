#ifndef BOMB_H
#define BOMB_H

#include <iostream>
using namespace std;

class Bomb {
private:
    int x, y;     // position on map
    int timer;    // countdown before explosion
    int power;    // explosion range

public:
    Bomb(int _x, int _y, int _timer = 3, int _power = 1)
        : x(_x), y(_y), timer(_timer), power(_power) {}

    void tick() { if (timer > 0) timer--; }

    bool hasExploded() const { return timer == 0; }

    int getTimer() const { return timer; }
    int getX() const { return x; }
    int getY() const { return y; }
    int getPower() { return power; }
};

#endif
