#ifndef GAME_H
#define GAME_H

#include "Map.h"
#include "Bomberman.h"
#include "Bomb.h"
#include "Enemy.h"
#include <vector>
#include <conio.h>
#include <iostream>
using namespace std;

class Game {
private:
    Map map;
    Bomberman player;
    vector<Bomb> bombs;
    vector<Enemy> enemies;
    bool running;

public:
    #define INITIAL_BOMB_COUNT 10

    Game() : player("Bomberman", 10, 1, INITIAL_BOMB_COUNT, 4, 4), running(true) {
        // Add some enemies
        enemies.push_back(Enemy("Enemy1",1,1));
        enemies.push_back(Enemy("Enemy2",6,8));
    }

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
            for(auto &b : bombs) 
                b.tick();

            // Explode bombs
            for(int i=bombs.size()-1;i>=0;i--){
                if(bombs[i].hasExploded()){
                    map.explodeBomb(bombs[i].getX(),bombs[i].getY());
                    bombs.erase(bombs.begin()+i);
                }
            }

            // Move enemies
            for(auto &e : enemies) e.moveRandom(map);
        }
        cout << "Thanks for playing!\n";
    }
};

#endif
