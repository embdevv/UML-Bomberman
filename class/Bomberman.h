#ifndef BOMBERMAN_H
#define BOMBERMAN_H

#include "Player.h"
#include "Map.h"
#include "Bomb.h"
#include <vector>

class Bomberman : public Player {
private:
    int bombs;
public:
    Bomberman(string n, int hp, int dmg, int bombCount) : Player(n,hp,dmg), bombs(bombCount) {}

    int getBombs() { return bombs; }

    void move(Map &map, char dir) {
        int x=-1, y=-1;
        for(int i=0;i<MAP_SIZE;i++)
            for(int j=0;j<MAP_SIZE;j++)
                if(map.getTile(i,j)=='P'){ x=i; y=j; break; }
        if(x==-1) return;

        int newX = x, newY = y;
        switch(dir) {
            case 'w': newX--; break;
            case 's': newX++; break;
            case 'a': newY--; break;
            case 'd': newY++; break;
            default: return;
        }

        if(map.getTile(newX,newY)==' ') {
            map.setTile(x,y,' ');
            map.setTile(newX,newY,'P');
        }
    }

    void placeBomb(Map &map, vector<Bomb> &bombsVec) {
    if(bombs>0){
        int x=-1, y=-1;
        for(int i=0;i<MAP_SIZE;i++)
            for(int j=0;j<MAP_SIZE;j++)
                if(map.getTile(i,j)=='P'){ x=i; y=j; break; }
        if(x==-1) return;
        bombs--;
        Bomb newBomb(x, y, 3, 1);
        newBomb.activate(); // <- activate right away
        bombsVec.push_back(newBomb);
        cout << getName() << " placed a bomb!" << endl;
    } else {
        cout << "No bombs left!" << endl;
    }
}

};

#endif
