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

    void printUI(){
                cout << "-----------------------------\n";
                cout << "Player (P): " << player.getName() 
                    << " | HP: " << player.getHp() 
                    << " | DMG: " << player.getDamage() 
                    << " | Bombs: " << player.getBombs() << endl;

                for(auto &e : enemies) {
                    cout << "Enemy: " << e.getName() 
                        << " | Position: (" << e.getX() << "," << e.getY() << ")"
                        << " | HP: " << e.getHp() 
                        << " | DMG: " << e.getDamage() << endl;
                }
                cout << "-----------------------------\n";
            }

    Game() : player("Bomberman", 25, 5, INITIAL_BOMB_COUNT, 4, 4), running(true) {
        // Add some enemies
        enemies.push_back(Enemy("Leaper",  5, 4, 1,1));
        enemies.push_back(Enemy("Brawler", 10, 10, 6,8));
    }

    void run() {
        char input;
        while(running){
            system("cls");
            printUI();

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
            // Tick bombs after printing
            for (auto &b : bombs)
                b.tick();

            // Explode bombs
            for (int i = bombs.size()-1; i >= 0; i--) {
                if (bombs[i].hasExploded()) {
                    map.explodeBomb(bombs[i].getX(), bombs[i].getY());
                    bombs.erase(bombs.begin() + i);
                }
            }


            // Move enemies
            for(auto &e : enemies) e.moveRandom(map);
        }
        cout << "Thanks for playing!\n";
    }
};

#endif
