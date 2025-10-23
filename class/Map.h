#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <vector>
#include "Bomb.h"
#include "Wall.h"
#include "Player.h"
using namespace std;

#define MAP_SIZE 9

class Map {
private:
    vector<vector<Wall*>> walls;  // 2D vector for walls
    char entities[MAP_SIZE][MAP_SIZE];  // For dynamic entities (P, E, bombs)

public:
    Map() {
        walls.resize(MAP_SIZE, vector<Wall*>(MAP_SIZE, nullptr));
        // Initialize walls and entities
        for (int i = 0; i < MAP_SIZE; i++) {
            for (int j = 0; j < MAP_SIZE; j++) {
                entities[i][j] = ' ';
                if (i == 0 || i == MAP_SIZE - 1 || j == 0 || j == MAP_SIZE - 1) {
                    walls[i][j] = new UnbreakableWall();  // Borders
                    entities[i][j] = '#';
                } else if ((i == 2 && (j == 2 || j == 4 || j == 6)) ||
                           (i == 4 && (j == 2 || j == 6)) ||
                           (i == 6 && (j == 2 || j == 4 || j == 6))) {  // Breakable wall positions (matching original 'B' placements)
                    walls[i][j] = new BreakableWall();
                    entities[i][j] = 'X';  // 'X' for breakable walls
                }
            }
        }
        // Set initial player position (ensure it's not overwritten by walls)
        entities[4][4] = 'P';
    }

    ~Map() {
        for (auto& row : walls) {
            for (auto& w : row) {
                delete w;
            }
        }
    }

    char getTile(int i, int j) const { return entities[i][j]; }
    void setTile(int i, int j, char c) { entities[i][j] = c; }

    bool isValidMove(int i, int j) const {
        return i >= 0 && i < MAP_SIZE && j >= 0 && j < MAP_SIZE && entities[i][j] == ' ';
    }

    void print(const vector<Bomb>& bombs) {
        char display[MAP_SIZE][MAP_SIZE];
        // Copy entities
        for (int i = 0; i < MAP_SIZE; i++)
            for (int j = 0; j < MAP_SIZE; j++)
                display[i][j] = entities[i][j];

        // Overlay bombs
        for (const auto& b : bombs) {
            if (!b.hasExploded())
                display[b.getX()][b.getY()] = '0' + b.getTimer();
        }

        // Print
        for (int i = 0; i < MAP_SIZE; i++) {
            for (int j = 0; j < MAP_SIZE; j++)
                cout << display[i][j] << ' ';
            cout << endl;
        }
    }

    // Explode bomb: destroy walls/entities in range, return list of positions hit
    vector<pair<int, int>> explodeBomb(int x, int y, int power) {
        vector<pair<int, int>> hitPositions;
        entities[x][y] = ' ';  // Clear bomb
        int dx[4] = {-1, 1, 0, 0};
        int dy[4] = {0, 0, -1, 1};
        for (int d = 0; d < 4; d++) {
            for (int r = 1; r <= power; r++) {
                int nx = x + dx[d] * r, ny = y + dy[d] * r;
                if (nx < 0 || nx >= MAP_SIZE || ny < 0 || ny >= MAP_SIZE) break;
                if (walls[nx][ny] && walls[nx][ny]->isDestructible()) {
                    delete walls[nx][ny];
                    walls[nx][ny] = nullptr;
                    entities[nx][ny] = ' ';
                    hitPositions.push_back({nx, ny});
                    break;  // Stop at destructible wall
                } else if (entities[nx][ny] != ' ') {
                    hitPositions.push_back({nx, ny});
                    // Don't clear unbreakable walls or entities here (handled in Game)
                }
            }
        }
        cout << "BOOM!!!\n";
        return hitPositions;
    }
};

#endif