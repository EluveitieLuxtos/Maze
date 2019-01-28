#include <algorithm>
#include <cstddef>
//#include <iostream>
#include <memory>
#include <vector>

#include "Door.h"
#include "DisjointSet.h"
#include "MazeWithWalls.h"
#include "TileTriangle.h"
#include "TileSquare.h"
#include "TileHexagon.h"
#include "TileM1Square1.h"
#include "TileM1Square2.h"
#include "Wall.h"

using namespace std;

MazeWithWalls::MazeWithWalls(){}

MazeWithWalls::MazeWithWalls(MazeType tinit, int winit, int cyclesNumber)
    :type(tinit), width(winit), length(winit){
    createTiling();
    createWalls();
    pathMergingMethod(0, cyclesNumber);
}

MazeWithWalls::MazeWithWalls(MazeType tinit, int winit, int linit, int cyclesNumber, int setsNumber)
    :type(tinit), width(winit), length(linit){
    createTiling();
    createWalls();
    pathMergingMethod(setsNumber, cyclesNumber);
}

MazeWithWalls::~MazeWithWalls(){}

void MazeWithWalls::createTiling(){
    int id = 0;
    switch (type) {
        case TRIANGLE:
            for (int i=0; i< width; i++)
                for (int j=0; j < 2*i+1; j++) {
                    TileTriangle tile = TileTriangle(id, i, j);
                    tiles.push_back(make_shared<TileTriangle>(tile));
                    id++;
                }
            break;
        case SQUARE:
            for (int i=0; i< width; i++)
                for (int j=0; j< length; j++) {
                    TileSquare tile = TileSquare(id, i, j);
                    tiles.push_back(make_shared<TileSquare>(tile));
                    id++;
                }
            break;
        case HEXAGON:
            for (int i=0; i< width; i++)
                for (int j=0; j< length; j++) {
                    TileHexagon tile = TileHexagon(id, i, j);
                    tiles.push_back(make_shared<TileHexagon>(tile));
                    id++;
                }
            break;
        case M1_SQUARES:
            for (int i=0; i< width; i++)
                for (int j=0; j< length; j++) {
                    tiles.push_back(make_shared<TileM1Square1>(TileM1Square1(id,i,j)));
                    id++;
                    for (int k=0; k< 4; k++) {
                        tiles.push_back(make_shared<TileM1Square2>(TileM1Square2(id,i,j)));
                        id++;
                    }
                }
            break;
        default:
            break;
    }
}

void MazeWithWalls::createWalls(){
    //Create all the walls around all the tiles
    //Unicity is made by comparing the hashcodes of visited tiles
//    cout << "creating walls with " << tiles.size() << " tiles" << endl;
    for (unsigned int i=0; i < tiles.size(); i++) {
        vector<int> currentlyVisited = tiles[i]->getNeighbours(width, length);
//        cout << "creating walls boucle " << i << " with " << currentlyVisited.size() << " neighbours" << endl;
        for (unsigned int j=0; j < currentlyVisited.size(); j++) {
//            cout << "creating walls boucle " << i << " " << j << endl;
            Wall wall = Wall(tiles[i], tiles[currentlyVisited[j]]);
            int currentHash = wall.hashcode();
            unsigned int k = 0, ws = walls.size();
            while (k < ws && currentHash != walls[k].hashcode()){
                k++;
            }
            if (k == ws) {
//                cout << "creating walls pushing " << tiles[i]->getX() << " " << tiles[i]->getY() << " ";
//                cout << currentlyVisited[j]->getX() << " " << currentlyVisited[j]->getY() << endl;
                walls.push_back(wall);
            }
        }
    }
//    cout << "creating walls final count " << walls.size() << endl;
    random_shuffle(walls.begin(),walls.end());
}

void MazeWithWalls::pathMergingMethod(int setsNumber, int cyclesNumber){
    //Method from Wikipedia using a forest disjoint set

//    cout << "path merging init : " << width << " " << length << endl;
    map<int,int> identification;
    for (unsigned int i = 0; i < tiles.size(); i++){
        identification.insert(make_pair(i, 0));
    }
    mp::DisjointSetForest<int> identificationSet(identification);
//    cout << "path merging disjoint set forest initialized" << endl;

    int wallsToDestroy = tiles.size() - setsNumber;
//    cout << "walls to destroy " << wallsToDestroy << endl;
    for (int i = 0; i < wallsToDestroy; i++){
//        cout << "path merging boucle " << i << endl;
        int j = 0;
        int id1 = walls[j].getT1()->getId();
        int id2 = walls[j].getT2()->getId();
//        cout << "path merging ids " << id1 << " " << id2 << endl;
        int set1 = identificationSet.find_set(id1);
        int set2 = identificationSet.find_set(id2);
//        cout << "path merging sets " << set1 << " " << set2 << endl;
        while (set1 == set2){
            j++;
            id1 = walls[j].getT1()->getId();
            id2 = walls[j].getT2()->getId();
//            cout << "path merging ids " << id1 << " " << id2 << " j " << j << " i " << i << endl;
            set1 = identificationSet.find_set(id1);
            set2 = identificationSet.find_set(id2);
        }
//        cout << "path merging destroying " << walls[j].getT1()->getX() << " " << walls[j].getT1()->getY() << " ";
//        cout << walls[j].getT2()->getX() << " " << walls[j].getT2()->getY() << endl;
        identificationSet.link(set1, set2);
        walls.erase(walls.begin()+j);
    }
//    cout << "path merging walls destroyed " << walls.size() << endl;

    if (setsNumber == 1) {
        for (int i = 0; i < cyclesNumber; i++){
            cycles.push_back(walls[i]);
            walls.erase(walls.begin()+i);
        }
    } else {
        for (int i = 0; i < setsNumber - 1; i++){
            int j = 0;
            int id1 = walls[j].getT1()->getId();
            int id2 = walls[j].getT2()->getId();
            int set1 = identificationSet.find_set(id1);
            int set2 = identificationSet.find_set(id2);
            while (set1 == set2){
                j++;
                id1 = walls[j].getT1()->getId();
                id2 = walls[j].getT2()->getId();
                set1 = identificationSet.find_set(id1);
                set2 = identificationSet.find_set(id2);
            }
            identificationSet.link(set1, set2);
            shared_ptr<Tile> t1 = walls[j].getT1();
            shared_ptr<Tile> t2 = walls[j].getT2();
            doors.push_back(Door(t1, t2));
            walls.erase(walls.begin()+j);
        }

        for (int i = 0; i < cyclesNumber; i++){
//            Erase walls in the same set
            int j = 0;
            int id1 = walls[j].getT1()->getId();
            int id2 = walls[j].getT2()->getId();
            int set1 = identificationSet.find_set(id1);
            int set2 = identificationSet.find_set(id2);
            while (set1 != set2){
                j++;
                id1 = walls[j].getT1()->getId();
                id2 = walls[j].getT2()->getId();
                set1 = identificationSet.find_set(id1);
                set2 = identificationSet.find_set(id2);
            }
            cycles.push_back(walls[j]);
            walls.erase(walls.begin()+j);
        }
    }
//    cout << "path merging finished" << endl;
}

MazeType MazeWithWalls::getType(){return type;}

int MazeWithWalls::getWidth(){return width;}

int MazeWithWalls::getLength(){return length;}

vector<shared_ptr<Tile>> MazeWithWalls::getTiles(){return tiles;}

vector<Wall> MazeWithWalls::getWalls(){return walls;}

vector<Wall> MazeWithWalls::getCycles(){return cycles;}

vector<Door> MazeWithWalls::getDoors(){return doors;}



