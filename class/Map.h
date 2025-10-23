#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <vector>
#include "Bomb.h"
using namespace std;

#define MAP_SIZE 9

class Map {
private:
    char grid[MAP_SIZE][MAP_SIZE];
public:
    Map() {
        char temp[MAP_SIZE][MAP_SIZE] = {
            {'#','#','#','#','#','#','#','#','#'},
            {'#',' ',' ',' ',' ',' ',' ',' ','#'},
            {'#',' ','B',' ','B',' ','B',' ','#'},
            {'#',' ',' ',' ',' ',' ',' ',' ','#'},
            {'#',' ','B',' ','P',' ','B',' ','#'},
            {'#',' ',' ',' ',' ',' ',' ',' ','#'},
            {'#',' ','B',' ','B',' ','B',' ','#'},
            {'#',' ',' ',' ',' ',' ',' ',' ','#'},
            {'#','#','#','#','#','#','#','#','#'}
        };
        for(int i=0;i<MAP_SIZE;i++)
            for(int j=0;j<MAP_SIZE;j++)
                grid[i][j] = temp[i][j];
    }

    char getTile(int i, int j) const { return grid[i][j]; }
    void setTile(int i, int j, char c) { grid[i][j] = c; }

    void print(const vector<Bomb>& bombs) {
        char display[MAP_SIZE][MAP_SIZE];

        // copy map layout
        for (int i = 0; i < MAP_SIZE; i++)
            for (int j = 0; j < MAP_SIZE; j++)
                display[i][j] = grid[i][j];

        // display bombs with timer
        for (const auto &b : bombs) {
            if (!b.hasExploded())
                display[b.getX()][b.getY()] = '0' + b.getTimer(); // shows 3,2,1
        }

        // print map
        for (int i = 0; i < MAP_SIZE; i++) {
            for (int j = 0; j < MAP_SIZE; j++)
                cout << display[i][j] << ' ';
            cout << endl;
        }
    }


    void explodeBomb(int x, int y) {
        grid[x][y] = ' '; // remove bomb
        int dx[4] = {-1,1,0,0};
        int dy[4] = {0,0,-1,1};
        for(int i=0;i<4;i++){
            int nx=x+dx[i], ny=y+dy[i];
            if(nx>=0 && nx<MAP_SIZE && ny>=0 && ny<MAP_SIZE){
                if(grid[nx][ny]=='B') grid[nx][ny]=' ';
            }
        }
        cout << "BOOM!!!\n";
    }
};

#endif
