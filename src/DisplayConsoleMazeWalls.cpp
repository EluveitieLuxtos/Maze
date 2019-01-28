#include <iostream>
#include <vector>

#include "DisplayConsoleMazeWalls.h"
#include "MazeWithWalls.h"

using namespace std;

void displayConsoleMazeWalls(MazeWithWalls & maze) {
    switch (maze.getType()) {
        case TRIANGLE:
            displayTriangle(maze);
            break;
        case SQUARE:
            displaySquare(maze);
            break;
        case HEXAGON:
            displayHexagon(maze);
            break;
        case M1_SQUARES:
            displayM1Squares(maze);
        default:
            break;
    }
}

template<typename T>
void setTiledCoordTriangle(vector<vector<TileType>>& mazeTypes, vector<T>& intersections,
                   TileType tileType1, TileType tileType2 = TILE_VOID){
    if (tileType2 == TILE_VOID)
        tileType2 = tileType1;
    for (unsigned int i = 0; i < intersections.size();i++){
        int x1 = intersections[i].getT1()->getX();
        int y1 = intersections[i].getT1()->getY();
        int x2 = intersections[i].getT2()->getX();
        int y2 = intersections[i].getT2()->getY();
        //Différencier mur et tile dans le pattern final
        int xw, yw, xt, yt;
        if (y1%2 == 0) {
            xw = 2*x2; yw = 2*y2; xt = 2*x1; yt = 2*y1;
        }
        else {
            xw = 2*x1; yw = 2*y1; xt = 2*x2; yt = 2*y2;
        }
        if (xw > xt) {
            mazeTypes[xt+1][yt] = tileType1;
            mazeTypes[xt+1][yt+1] = tileType2;
            mazeTypes[xt+1][yt+2] = tileType1;
        } else if (yw > yt) {
            mazeTypes[xt-1][yt] = tileType1;
            mazeTypes[xt][yt+1] = tileType2;
            mazeTypes[xt][yt+2] = tileType1;
        } else {
            mazeTypes[xt-1][yt-2] = tileType1;
            mazeTypes[xt][yt-1] = tileType2;
            mazeTypes[xt][yt-2] = tileType1;
        }
    }
}

void displayTriangle(MazeWithWalls & maze){
    //Code spaghetti pour vérifier la génération d'un labyrinthe avec des cases triangulaires
    vector<Wall> walls = maze.getWalls();
    vector<Wall> cycles = maze.getCycles();
    vector<Door> doors = maze.getDoors();
    vector<vector<TileType>> mazeTypes;
    int width = 2*maze.getWidth()-1;
    for (int i=0; i < width; i++){
        mazeTypes.push_back(vector<TileType>(2*i+1, TILE_FLOOR));
    }

    setTiledCoordTriangle<Wall>(mazeTypes, walls, TILE_WALL);
    setTiledCoordTriangle<Wall>(mazeTypes, cycles, TILE_FLOOR, TILE_MOB_SPAWNER);
    setTiledCoordTriangle<Door>(mazeTypes, doors, TILE_DOOR);

//    tiles lost because of the triangle pattern
    for (int i=0; i < maze.getWidth()-2; i++){
        for (int j=0; j < i+1;j++){
            mazeTypes[2*i+3][4*j+3] = TILE_WALL;
        }
    }

    for (int i = 0; i < width;i++){
        for (int j = 0; j < width - i -1; j++)
            cout << " ";
        for (int j = 0; j < 2*i+1; j++){
            switch (mazeTypes[i][j]) {
                case TILE_WALL:
                    if (j%2 == 0)
                        cout << "A";
                    else
                        cout << "V";
                    break;
                case TILE_FLOOR:
                    cout << ".";
                    break;
                case TILE_DOOR:
                    cout << "D";
                    break;
                case TILE_MOB_SPAWNER:
                    cout << "*";
                    break;
                default:
                    cout << "#";
                    break;
            }
        }
        cout << endl;
    }
}

template<typename T>
void setTiledCoordSquare(vector<vector<TileType>>& mazeTypes, vector<T>& intersections, TileType tileType){
    for (unsigned int i = 0; i < intersections.size();i++){
        int x1 = intersections[i].getT1()->getX();
        int y1 = intersections[i].getT1()->getY();
        int x2 = intersections[i].getT2()->getX();
        int y2 = intersections[i].getT2()->getY();
        mazeTypes[x1+x2][y1+y2] = tileType;
    }
}

void displaySquare(MazeWithWalls & maze){
    //Code spaghetti pour vérifier la génération d'un labyrinthe avec des cases carrées
    vector<Wall> walls = maze.getWalls();
    vector<Wall> cycles = maze.getCycles();
    vector<Door> doors = maze.getDoors();
    vector<vector<TileType>> mazeTypes;
    int width = 2*maze.getWidth()-1;
    int length = 2*maze.getLength()-1;
    mazeTypes.resize(width,vector<TileType>(length,TILE_FLOOR));

    setTiledCoordSquare<Wall>(mazeTypes, walls, TILE_WALL);
    setTiledCoordSquare<Wall>(mazeTypes, cycles, TILE_MOB_SPAWNER);
    setTiledCoordSquare<Door>(mazeTypes, doors, TILE_DOOR);

//    tiles lost because of the square pattern
    for (int i=0; i < maze.getWidth()-1;i++){
        for (int j=0; j < maze.getLength()-1;j++){
            mazeTypes[2*i+1][2*j+1] = TILE_WALL;
        }
    }

    for (int i = 0; i < width;i++){
        for (int j = 0; j < length;j++){
            switch (mazeTypes[i][j]) {
                case TILE_WALL:
                    cout << "W";
                    break;
                case TILE_FLOOR:
                    cout << ".";
                    break;
                case TILE_DOOR:
                    cout << "D";
                    break;
                case TILE_MOB_SPAWNER:
                    cout << "*";
                    break;
                default:
                    cout << "#";
                    break;
            }
        }
        cout << endl;
    }
}

template<typename T>
void setTiledCoordHexagon(vector<vector<TileType>>& mazeTypes, vector<T>& intersections, TileType tileType){
    for (unsigned int i = 0; i < intersections.size();i++){
        int x1 = intersections[i].getT1()->getX();
        int y1 = intersections[i].getT1()->getY();
        int x2 = intersections[i].getT2()->getX();
        int y2 = intersections[i].getT2()->getY();
        if ((y1+y2+2)%4 == 0) {
            mazeTypes[x1+x2+1][y1+y2] = tileType;
        } else {
            mazeTypes[x1+x2][y1+y2] = tileType;
        }
    }
}

void displayHexagon(MazeWithWalls & maze){
    //Code spaghetti pour vérifier la génération d'un labyrinthe avec des cases hexagonales
    vector<Wall> walls = maze.getWalls();
    vector<Wall> cycles = maze.getCycles();
    vector<Door> doors = maze.getDoors();
    vector<vector<TileType>> mazeTypes;
    int width = 2*maze.getWidth();
    int length = 2*maze.getLength()-1;
    mazeTypes.resize(width,vector<TileType>(length,TILE_FLOOR));

    setTiledCoordHexagon<Wall>(mazeTypes, walls, TILE_WALL);
    setTiledCoordHexagon<Wall>(mazeTypes, cycles, TILE_MOB_SPAWNER);
    setTiledCoordHexagon<Door>(mazeTypes, doors, TILE_DOOR);

//    tiles lost because of the hexagon pattern
    for (int j=0; j < length; j++){
        if ((j+2)%4 == 0)
            mazeTypes[0][j] = TILE_WALL;
        else
            mazeTypes[width-1][j] = TILE_WALL;
    }

//    affichage de la transposée
    for (int i = 0; i < length; i++){
        if (i%2 == 1)
            cout << " ";
        for (int j = 0; j < width; j++){
            switch (mazeTypes[j][i]) {
                case TILE_WALL:
                    cout << "WW";
                    break;
                case TILE_FLOOR:
                    cout << "..";
                    break;
                case TILE_DOOR:
                    cout << "DD";
                    break;
                case TILE_MOB_SPAWNER:
                    cout << "**";
                    break;
                default:
                    cout << "##";
                    break;
            }
        }
        cout << endl;
    }
}

void displayM1Squares(MazeWithWalls & maze){
    //Code spaghetti pour essayer d'afficher en console un labyrinthe fait en dallage
    //Abandon car non compatibilité de la console avec les dallages
    vector<Wall> walls = maze.getWalls();
    vector<Wall> cycles = maze.getCycles();
    vector<Door> doors = maze.getDoors();
    vector<vector<TileType>> mazeTypes;
    int mwidth = maze.getWidth();
    int mlength = maze.getLength();
    int width = 5*mwidth+3*mlength;
    int length = 3;

//    cout << "display init" << endl;
    for (int i = 0; i < width; i++){
        if (i>0) {
        if (i < 3*mlength && i%3 == 0)
            length+=5;
        else if (i > 3*mlength && (i-3*mlength)%5 == 0)
            length-=3;
        else if (i == 3*mlength)
            length += 2;
        if (i < 5*mwidth && i%5 == 0)
            length+=3;
        else if (i > 5*mwidth && (i-5*mwidth)%3 == 0)
            length-=5;
        }
        mazeTypes.push_back(vector<TileType>(length, TILE_FLOOR));
    }
//    cout << "display init matrix created" << endl;

//    setTiledCoordM1Squares<Wall>(mazeTypes, walls, TILE_WALL);
//    setTiledCoordM1Squares<Wall>(mazeTypes, cycles, TILE_MOB_SPAWNER);
//    setTiledCoordM1Squares<Door>(mazeTypes, doors, TILE_DOOR);

//    tiles lost because of the M1_Squares pattern
//    too difficult to do

    length = 3*mwidth;
    for (int i = 0; i < width; i++){
        if (i < 5*mwidth && i%5 == 0)
            length-=3;
        else if (i > 5*mwidth && (i-5*mwidth)%3 == 0)
            length+=5;
        for (int k = 0; k<length; k++)
            cout << " ";
        for (unsigned int j = 0; j < mazeTypes[i].size(); j++){
            switch (mazeTypes[i][j]) {
                case TILE_WALL:
                    cout << "W";
                    break;
                case TILE_FLOOR:
                    cout << ".";
                    break;
                case TILE_DOOR:
                    cout << "D";
                    break;
                case TILE_MOB_SPAWNER:
                    cout << "*";
                    break;
                default:
                    cout << "#";
                    break;
            }
        }
        cout << endl;
    }
}




