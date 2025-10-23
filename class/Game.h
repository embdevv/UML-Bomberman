#ifndef GAME_H
#define GAME_H

#include "Map.h"
#include "Bomberman.h"
#include "Bomb.h"
#include "Enemy.h"
#include <vector>
#include <conio.h>
#include <iostream>
#include <ctime>  // For srand
#include <algorithm>  // For remove_if
using namespace std;

#define INITIAL_BOMB_COUNT 10

class Game {
private:
    Map map;
    Bomberman player;
    vector<Bomb> bombs;
    vector<Enemy> enemies;
    bool running;

public:
    Game() : player("Bomberman", 10, 1, INITIAL_BOMB_COUNT), running(true) {
        srand(time(0));  // Seed random
        enemies.push_back(Enemy("Leaper", 5, 1, 1, 1, 2));
        enemies.push_back(Enemy("Tank", 10, 3, 6, 6, 1));
        for (auto& e : enemies) {
            map.setTile(e.getX(), e.getY(), 'E');
        }
    }

    void run() {
        char input;
        while (running) {
            system("cls");
            map.print(bombs);
            player.displayInfo();
            cout << "Enemies:\n";
            for (auto& e : enemies) {
                e.displayInfo();
            }
            cout << "Move: W/A/S/D | Bomb: B | Quit: Q\n";

            input = _getch();
            if (input == 'w' || input == 'a' || input == 's' || input == 'd')
                player.move(map, input);
            else if (input == 'b' || input == 'B')
                player.placeBomb(map, bombs);
            else if (input == 'q' || input == 'Q')
                running = false;

            // Tick bombs
            for (auto& b : bombs) b.tick();

            // Explode bombs and damage entities
            for (int i = bombs.size() - 1; i >= 0; i--) {
                if (bombs[i].hasExploded()) {
                    auto hitPositions = map.explodeBomb(bombs[i].getX(), bombs[i].getY(), bombs[i].getPower());
                    // Damage player if in blast
                    for (auto& pos : hitPositions) {
                        if (pos.first == player.getX() && pos.second == player.getY()) {
                            player.takeDamage(1);
                        }
                    }
                    // Damage enemies
                    for (auto& e : enemies) {
                        for (auto& pos : hitPositions) {
                            if (pos.first == e.getX() && pos.second == e.getY()) {
                                e.takeDamage(1);
                            }
                        }
                    }
                    bombs.erase(bombs.begin() + i);
                }
            }

            // Remove dead enemies
            enemies.erase(remove_if(enemies.begin(), enemies.end(),
                [](const Enemy& e) { return e.getHp() <= 0; }), enemies.end());

            // Move enemies
            for (auto& e : enemies) e.moveRandom(map);

            // Check win/lose
            if (player.getHp() <= 0) {
                cout << "You lose! Game over.\n";
                running = false;
            } else if (enemies.empty()) {
                cout << "You win! All enemies defeated.\n";
                running = false;
            }
        }
        cout << "Thanks for playing!\n";
    }
};

#endif