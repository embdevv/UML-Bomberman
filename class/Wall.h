#ifndef WALL_H
#define WALL_H

class Wall {
protected:
    bool destructible;
public:
    Wall(bool d) : destructible(d) {}
    bool isDestructible() { return destructible; }
};

class BreakableWall : public Wall {
public:
    BreakableWall() : Wall(true) {}
};

class UnbreakableWall : public Wall {
public:
    UnbreakableWall() : Wall(false) {}
};

#endif
    // WALL_H