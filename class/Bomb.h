#ifndef BOMB_H
#define BOMB_H

#include <iostream>
using namespace std;

class Bomb {
private:
    int x, y;      // coordinates on the map
    int timer;     // countdown ticks
    int power;     // explosion range
    bool exploded;

public:
    Bomb(int _x, int _y, int _timer = 3, int _power = 1)
        : x(_x), y(_y), timer(_timer), power(_power), exploded(false) {}

    int getX() const { return x; }
    int getY() const { return y; }
    int getTimer() const { return timer; }
    int getPower() const { return power; }
    bool hasExploded() const { return exploded; }

    void tick() {
        if (!exploded && timer > 0) {
            timer--;
            if (timer == 0) exploded = true;
        }
    }
};

#endif
