#ifndef GAME_H
#define GAME_H

#include "Map.h"
#include "Bomberman.h"
#include "Bomb.h"
#include <vector>
#include <conio.h>
#include <iostream>
using namespace std;

class Game {
private:
    Map map;
    Bomberman player;
    vector<Bomb> bombs;
    bool running;
public:
    Game() : player("Bomberman", 10, 1, 3), running(true) {}

    void run() {
        char input;
        while(running){
            system("cls");
            map.print(bombs);
            cout << "Move: W/A/S/D | Bomb: B | Quit: Q\nBombs left: " << player.getBombs() << endl;

            input = _getch();

            if(input=='w'||input=='a'||input=='s'||input=='d')
                player.move(map,input);
            else if(input=='b'||input=='B')
                player.placeBomb(map,bombs);
            else if(input=='q'||input=='Q')
                running=false;

            // Tick bombs
            for(auto &b : bombs){
                if(!b.hasExploded()) b.tick();
                if(b.hasExploded()) map.explodeBomb(b.getX(),b.getY());
            }

            // Remove exploded bombs
            for(int i=bombs.size()-1;i>=0;i--){
                if(bombs[i].hasExploded()) bombs.erase(bombs.begin()+i);
            }
        }
        cout << "Thanks for playing!" << endl;
    }
};

#endif
