#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <vector>
#include "Bomb.h"
using namespace std;

#define MAP_WIDTH 10
#define MAP_HEIGHT 8

class Map {
private:
    char tiles[MAP_HEIGHT][MAP_WIDTH];

public:
    Map() {
        // Initialize a simple map with walls and empty space
        const char defaultMap[MAP_HEIGHT][MAP_WIDTH] = {
            {'#','#','#','#','#','#','#','#','#','#'},
            {'#',' ','B',' ','B',' ','B',' ',' ','#'},
            {'#',' ',' ',' ',' ',' ',' ',' ',' ','#'},
            {'#','B',' ',' ',' ',' ',' ','B',' ','#'},
            {'#',' ',' ','P',' ',' ',' ',' ',' ','#'},
            {'#',' ',' ',' ',' ','B',' ',' ',' ','#'},
            {'#',' ','B',' ',' ',' ',' ','B',' ','#'},
            {'#','#','#','#','#','#','#','#','#','#'}
        };
        for(int i=0;i<MAP_HEIGHT;i++)
            for(int j=0;j<MAP_WIDTH;j++)
                tiles[i][j] = defaultMap[i][j];
    }

    char getTile(int x, int y) const {
        if(x<0 || x>=MAP_HEIGHT || y<0 || y>=MAP_WIDTH) return '#';
        return tiles[x][y];
    }

    void setTile(int x, int y, char value) {
        if(x<0 || x>=MAP_HEIGHT || y<0 || y>=MAP_WIDTH) return;
        tiles[x][y] = value;
    }

    // Print map with bombs
    void print(const vector<Bomb> &bombs) const {
        char display[MAP_HEIGHT][MAP_WIDTH];
        for(int i=0;i<MAP_HEIGHT;i++)
            for(int j=0;j<MAP_WIDTH;j++)
                display[i][j] = tiles[i][j];

        for(auto &b : bombs){
            if(!b.hasExploded())
                display[b.getX()][b.getY()] = '*';
        }

        for(int i=0;i<MAP_HEIGHT;i++){
            for(int j=0;j<MAP_WIDTH;j++)
                cout << display[i][j] << ' ';
            cout << endl;
        }
    }

    // Explode bomb at position
    void explodeBomb(int x, int y) {
        tiles[x][y] = ' ';
        int dx[4] = {-1,1,0,0};
        int dy[4] = {0,0,-1,1};
        for(int i=0;i<4;i++){
            int nx = x+dx[i], ny=y+dy[i];
            if(nx>=0 && nx<MAP_HEIGHT && ny>=0 && ny<MAP_WIDTH){
                if(tiles[nx][ny] == 'B') tiles[nx][ny] = ' ';
            }
        }
        cout << "BOOM!\n";
    }
};

#endif
