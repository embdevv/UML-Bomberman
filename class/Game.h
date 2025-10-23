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
#include <thread>     // For sleep (optional for smoothness)
#include <chrono>     // For sleep
using namespace std;

#define INITIAL_BOMB_COUNT 15

class Game {
private:
    Map map;
    Bomberman player;
    vector<Bomb> bombs;
    vector<Enemy*> enemies;  // Changed to pointers for polymorphism (subclasses like Leaper/Tank)
    bool running;

    string lastMessage;     // <-- new: text to display after board
    int messageTimer;       // <-- new: how many frames to show it

public:
    Game() : player("Bomberman", 10, 5, INITIAL_BOMB_COUNT), running(true) {
        srand(time(0));  // Seed random
        // Use subclasses for different enemy behaviors (update if you have Leaper/Tank classes)
        enemies.push_back(new Leaper(1,1));  // Example: Leaper moves 2 tiles
        enemies.push_back(new Brawler(6,6));   // Example: Tank moves 1 tile, tougher
        for (auto& e : enemies) {
            map.setTile(e->getX(), e->getY(), 'E');
        }
    }

    ~Game() {
        for (auto& e : enemies) delete e;  // Clean up pointers
    }

    void run() {
        cout << "Welcome to Terminal Bomberman!" << endl;
        cout << "Controls: W/A/S/D to move, B to bomb, Q to quit." << endl;
        cout << "Press any key to start..." << endl;
        _getch();  // Wait for user to start

        char input;
        while (running) {
            system("cls");  // Clear screen for clean display
            map.print(bombs);  // Print the grid with entities/bombs

            if (messageTimer > 0)   {
                cout << lastMessage << endl;
                --messageTimer;
            }

            cout << endl;  // Spacer for readability
            player.displayInfo();
            cout << "Enemies:" << endl;
            for (auto& e : enemies) {
                e->displayInfo();
            }
            cout << "Move: W/A/S/D | Bomb: B | Quit: Q" << endl;

            input = _getch();
            if (input == 'w' || input == 'a' || input == 's' || input == 'd') {
                player.move(map, input);
                cout << "Hero moved to (" << player.getX() << ", " << player.getY() << ")." << endl;
            } else if (input == 'b' || input == 'B') {
                player.placeBomb(map, bombs);
                // Message already in placeBomb()
            } else if (input == 'q' || input == 'Q') {
                cout << "Quitting game..." << endl;
                running = false;
            } else {
                cout << "Invalid input! Use W/A/S/D/B/Q." << endl;
            }

            // Tick bombs
            for (auto& b : bombs) b.tick();

            // Explode bombs and damage entities
            for (int i = bombs.size() - 1; i >= 0; i--) {
                if (bombs[i].hasExploded()) {
                    auto hitPositions = map.explodeBomb(bombs[i].getX(), bombs[i].getY(), bombs[i].getPower());
                    
                    // NEW: Show explosion effect with 'o' on hit positions
                    system("cls");  // Clear screen
                    map.printWithExplosion(bombs, hitPositions);  // Call the new method
                    cout << endl;  // Spacer for readability
                    player.displayInfo();
                    cout << "Enemies:" << endl;
                    for (auto& e : enemies) {
                        e->displayInfo();
                    }
                    cout << "Move: W/A/S/D | Bomb: B | Quit: Q" << endl;
                    
                    // Damage player if in blast
                    for (auto& pos : hitPositions) {
                        if (pos.first == player.getX() && pos.second == player.getY()) {
                            player.takeDamage(1);
                            cout << "Player hit by explosion! HP now: " << player.getHp() << endl;
                        }
                    }
                    // Damage enemies
                    for (auto& e : enemies) {
                        for (auto& pos : hitPositions) {
                            if (pos.first == e->getX() && pos.second == e->getY()) {
                                e->takeDamage(1);
                                cout << e->getName() << " hit by explosion! HP now: " << e->getHp() << endl;
                            }
                        }
                    }
                    bombs.erase(bombs.begin() + i);
                }
            }

            // Remove dead enemies
            enemies.erase(remove_if(enemies.begin(), enemies.end(),
                [](Enemy* e) { return e->getHp() <= 0; }), enemies.end());

            // Move enemies
            for (auto& e : enemies) e->moveRandom(map);

            // Check win/lose
            if (player.getHp() <= 0) {
                cout << "You lose! Game over." << endl;
                running = false;
            } else if (!enemies.empty() && player.getBombs() == 0 && bombs.empty()) {
                // Only lose immediately if player has no bombs AND there are no active bombs on the map
                cout << "You lose! No bombs left and enemies remain." << endl;
                running = false;
            } else if (enemies.empty()) {
                cout << "You win! All enemies defeated." << endl;
                running = false;
            }
            
        }
        cout << "Thanks for playing Terminal Bomberman!" << endl;
    }
};

#endif