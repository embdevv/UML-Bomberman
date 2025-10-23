#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <vector>
#include "Bomb.h"
#include "Wall.h"
#include "Player.h"
using namespace std;

#define MAP_ROWS 15   ///< Number of rows in map  (height)
#define MAP_COLS 25   ///< Number of columns in map (width)

/**
 * @file Map.h
 * @brief Represents the Bomberman game map, including walls, player, and enemies.
 */

/**
 * @class Map
 * @brief Handles the game map, including wall placement, entity positions, and bomb explosions.
 */

class Map {
private:
    vector<vector<Wall*>> walls;    ///< 2D vector for walls
    vector<vector<char>> entities;  ///< 2D grid of entities like players and enemies

public:
    /**
     * @brief Constructor initializes map with walls and empty tiles.
     * @post Map is populated with unbreakable and breakable walls, player position set.
     */

    Map() {
        walls.resize(MAP_ROWS, vector<Wall*>(MAP_COLS, nullptr));
        entities.resize(MAP_ROWS, vector<char>(MAP_COLS, ' '));
        
        // Initialize walls and entities
        for (int i = 0; i < MAP_ROWS; i++) {
            for (int j = 0; j < MAP_COLS; j++) {
                entities[i][j] = ' ';
                
                // Create border walls
                if (i == 0 || i == MAP_ROWS - 1 || j == 0 || j == MAP_COLS - 1) {
                    walls[i][j] = new UnbreakableWall();
                    entities[i][j] = '#';
                }
                // Checkerboard unbreakable walls every 4th tile
                else if (i % 4 == 0 && j % 4 == 0) {
                    walls[i][j] = new UnbreakableWall();
                    entities[i][j] = '#';
                }
                // Add breakable walls with reduced 30% probability 
                else if (!(
                    (i >= 1 && i <= 3 && j >= 1 && j <= 3) ||  // Top-left area (player start)
                    (i >= MAP_ROWS-4 && i < MAP_ROWS-1 && j >= MAP_COLS-4 && j < MAP_COLS-1)  // Bottom-right area (enemy)
                )) {
                    if (rand() % 100 < 30 && entities[i][j] == ' ') {  
                        walls[i][j] = new BreakableWall();
                        entities[i][j] = 'X';
                    }
                }
            }
        }
        // Set initial player position in top-left corner
        entities[1][1] = 'P';
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

    /**
     * @brief Checks if a move to (i, j) is valid (within bounds and not blocked).
     * @param i Row index
     * @param j Column index
     * @return True if move is empty and within bounds, false otherwise.
     */
    bool isValidMove(int i, int j) const {
        return i >= 0 && i < MAP_ROWS && j >= 0 && j < MAP_COLS && entities[i][j] == ' ';
    }

    /**
     * @brief Prints the map with current entities and bombs.
     * @param bombs Vector of active bombs to display on the map.
     */
    void print(const vector<Bomb>& bombs) {
        vector<vector<char>> display = entities;  // Copy entities
        
        // Overlay bombs
        for (const auto& b : bombs) {
            if (!b.hasExploded())
                display[b.getX()][b.getY()] = '0' + b.getTimer();
        }

        // Print
        for (int i = 0; i < MAP_ROWS; i++) {
            for (int j = 0; j < MAP_COLS; j++)
                cout << display[i][j] << ' ';
            cout << endl;
        }
    }

    /**
     * @brief Prints the map with explosion effect (overlay 'o' on hit positions).
     * @param bombs Vector of active bombs to display on the map.
     * @param hitPositions Vector of positions affected by the explosion.
     */
    void printWithExplosion(const vector<Bomb>& bombs, const vector<pair<int, int>>& hitPositions) {
        vector<vector<char>> display = entities;  // Copy entities
        
        // Overlay bombs
        for (const auto& b : bombs) {
            if (!b.hasExploded())
                display[b.getX()][b.getY()] = '0' + b.getTimer();
        }
        
        // Overlay explosion 'o' on hit positions
        for (const auto& pos : hitPositions) {
            display[pos.first][pos.second] = 'o';
        }

        // Print
        for (int i = 0; i < MAP_ROWS; i++) {
            for (int j = 0; j < MAP_COLS; j++)
                cout << display[i][j] << ' ';
            cout << endl;
        }
    }

   /**
    * @brief Explode bomb at a given position
    * @param x X-coordinate of bomb
    * @param y Y-coordinate of bomb
    * @param power Explosion range
    * @return Vector of positions hit by the explosion
    * @post Destroys breakable walls and marks hit positions.
    */
    vector<pair<int, int>> explodeBomb(int x, int y, int power) {
        vector<pair<int, int>> hitPositions;
        entities[x][y] = ' ';  // Clear bomb
        int dx[4] = {-1, 1, 0, 0};
        int dy[4] = {0, 0, -1, 1};
        for (int d = 0; d < 4; d++) {
            for (int r = 1; r <= power; r++) {
                int nx = x + dx[d] * r, ny = y + dy[d] * r;
                if (nx < 0 || nx >= MAP_ROWS || ny < 0 || ny >= MAP_COLS) break;
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