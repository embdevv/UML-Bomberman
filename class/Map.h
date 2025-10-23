#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <vector>
#include "Wall.h"
#include "Bomb.h"
#define MAP_SIZE 7
using namespace std;

class Map {
private:
    char grid[MAP_SIZE][MAP_SIZE];
public:
    Map() {
        char initial[MAP_SIZE][MAP_SIZE] = {
            {'#','#','#','#','#','#','#'},
            {'#',' ','B',' ','B',' ','#'},
            {'#',' ',' ',' ',' ',' ','#'},
            {'#','B',' ','P',' ','B','#'},
            {'#',' ',' ',' ',' ',' ','#'},
            {'#',' ','B',' ','B',' ','#'},
            {'#','#','#','#','#','#','#'}
        };
        for(int i=0;i<MAP_SIZE;i++)
            for(int j=0;j<MAP_SIZE;j++)
                grid[i][j] = initial[i][j];
    }

    char getTile(int x, int y) { return grid[x][y]; }
    void setTile(int x, int y, char value) { grid[x][y] = value; }

    void explodeBomb(int x, int y) {
        grid[x][y] = ' ';
        int dx[4] = {-1,1,0,0};
        int dy[4] = {0,0,-1,1};
        for(int i=0;i<4;i++){
            int nx = x+dx[i], ny = y+dy[i];
            if(nx>=0 && nx<MAP_SIZE && ny>=0 && ny<MAP_SIZE){
                if(grid[nx][ny]=='B') grid[nx][ny]=' ';
                if(grid[nx][ny]=='P') cout << "Player hit by explosion!" << endl;
            }
        }
        cout << "BOOM!!!" << endl;
    }

    void print(vector<Bomb>& bombs) {
        for(int i=0;i<MAP_SIZE;i++){
            for(int j=0;j<MAP_SIZE;j++){
                bool bombHere = false;
                for(auto &b : bombs){
                    if(!b.hasExploded() && b.getX()==i && b.getY()==j){
                        cout << "* ";
                        bombHere = true;
                        break;
                    }
                }
                if(!bombHere) cout << grid[i][j] << " ";
            }
            cout << endl;
        }
    }
};

#endif
