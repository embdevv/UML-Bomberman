#ifndef BOMB_H
#define BOMB_H

class Bomb {
private:
    int x, y;
    int timer;
    int power;
    bool active;
public:
    Bomb(int px, int py, int t=3, int p=1) : x(px), y(py), timer(t), power(p), active(false) {}
    void activate() { active = true; }
    
    void tick() {
    if(!active) active = true; 
    if(timer > 0) timer--;
    }
 
    bool hasExploded() { return active && timer==0; }
    int getX() { return x; }
    int getY() { return y; }
    int getPower() { return power; }
};

#endif
