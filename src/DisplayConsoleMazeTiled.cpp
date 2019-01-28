#include <iostream>
#include <vector>

#include "DisplayConsoleMazeTiled.h"
#include "MazeTiled.h"

using namespace std;

void displayConsoleMazeTiled(MazeTiled& maze) {
    switch (maze.getType()) {
        case TRIANGLE:
            displayTiledTriangle(maze);
            break;
        case SQUARE:
            displayTiledSquare(maze);
            break;
        case HEXAGON:
            displayTiledHexagon(maze);
            break;
        default:
            break;
    }
}

void displayTiledTriangle(MazeTiled& maze){
    //Code spaghetti pour vérifier la génération d'un labyrinthe avec des cases triangulaires
    vector<shared_ptr<Tile>> tiles = maze.getTiles();
    int width = maze.getWidth();

    for (int i = 0; i < width;i++){
        for (int j = 0; j < width - i -1; j++)
            cout << " ";
        for (int j = 0; j < 2*i+1; j++){
            switch (tiles[maze.triangleID(i,j)]->getTileType()) {
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

void displayTiledSquare(MazeTiled& maze){
    //Code spaghetti pour vérifier la génération d'un labyrinthe avec des cases carrées
    vector<shared_ptr<Tile>> tiles = maze.getTiles();
    int width = maze.getWidth();
    int length = maze.getLength();

    for (int i = 0; i < width;i++){
        for (int j = 0; j < length;j++){
            switch (tiles[maze.squareID(i,j,length)]->getTileType()) {
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

void displayTiledHexagon(MazeTiled& maze){
    //Code spaghetti pour vérifier la génération d'un labyrinthe avec des cases hexagonales
//    affichage de la transposée
    vector<shared_ptr<Tile>> tiles = maze.getTiles();
    int width = maze.getWidth();
    int length = maze.getLength();

    for (int i = 0; i < length; i++){
        if (i%2 == 1)
            cout << " ";
        for (int j = 0; j < width; j++){
            switch (tiles[maze.hexagonID(j,i,length)]->getTileType()) {
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

