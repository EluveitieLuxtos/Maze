#include <memory>
#include <vector>

#include "Door.h"
#include "MazeWithWalls.h"
#include "MazeTiled.h"
#include "TileTriangle.h"
#include "TileSquare.h"
#include "TileHexagon.h"
#include "Wall.h"

MazeTiled::MazeTiled(){}

MazeTiled::MazeTiled(MazeType tinit, int winit, int cyclesNumber, bool externalWalls)
    :type(tinit){
    MazeWithWalls maze(tinit, winit, cyclesNumber);
    setTiling(maze, externalWalls);
}

MazeTiled::MazeTiled(MazeType tinit, int winit, int linit, int cyclesNumber, int setsNumber, bool externalWalls)
    :type(tinit){
    MazeWithWalls maze(tinit, winit, linit, cyclesNumber, setsNumber);
    setTiling(maze, externalWalls);
}

void MazeTiled::setTiling(MazeWithWalls& maze, bool externalWalls){
    switch (maze.getType()) {
        case TRIANGLE:
            setTriangleTiling(maze, externalWalls);
            break;
        case SQUARE:
            setSquareTiling(maze, externalWalls);
            break;
        case HEXAGON:
            setHexagonTiling(maze, externalWalls);
            break;
        default:
            break;
    }
}

void MazeTiled::setTriangleTiling(MazeWithWalls & maze, bool externalWalls){
    vector<Wall> walls = maze.getWalls();
    vector<Wall> cycleWalls = maze.getCycles();
    vector<Door> doorWalls = maze.getDoors();
    int offset = 0;
    if (externalWalls)
        offset=2; //offset must be pair
    width = 2*maze.getWidth()-1+offset;
    if (externalWalls)
        width+=1;
    int id = 0;
    for (int i=0; i < width; i++)
        for (int j=0; j < 2*i+1+2*offset; j++){
            tiles.push_back(make_shared<TileTriangle>(TileTriangle(id,i,j)));
            id++;
        }

    setTiledCoordTriangleWall<Wall>(walls, TILE_WALL, offset);
    setTiledCoordTriangleIntersect<Wall>(cycleWalls, mobspawners, TILE_FLOOR, TILE_MOB_SPAWNER, offset);
    setTiledCoordTriangleIntersect<Door>(doorWalls, doors, TILE_FLOOR, TILE_DOOR, offset);

//    tiles lost because of the triangle pattern
    for (int i=0; i < maze.getWidth()-2; i++)
        for (int j=0; j < i+1;j++)
            tiles[triangleID(2*i+3+offset, 4*j+3+offset)]->setTileType(TILE_WALL);
    if (externalWalls) {
        for (int i=0; i < offset; i++)
            for (int j=0; j < 2*i+1; j++)
                tiles[triangleID(i, j)]->setTileType(TILE_WALL);
        for (int i=offset; i < width-1; i++)
            for (int j=0; j < offset; j++){
                tiles[triangleID(i, j)]->setTileType(TILE_WALL);
                tiles[triangleID(i, 2*i-j)]->setTileType(TILE_WALL);
            }
        for (int j=0; j < 2*width; j++)
            tiles[triangleID(width-1, j)]->setTileType(TILE_WALL);
    }
}

void MazeTiled::setSquareTiling(MazeWithWalls & maze, bool externalWalls){
    vector<Wall> walls = maze.getWalls();
    vector<Wall> cycleWalls = maze.getCycles();
    vector<Door> doorWalls = maze.getDoors();
    int xoff = 0, yoff = 0;
    if (externalWalls){
        xoff = 1;
        yoff = 1;
    }
    width = 2*maze.getWidth()-1+2*xoff;
    length = 2*maze.getLength()-1+2*yoff;
    int id = 0;
    for (int i=0; i < width; i++)
        for (int j=0; j < length; j++){
            tiles.push_back(make_shared<TileSquare>(TileSquare(id,i,j)));
            id++;
        }

    setTiledCoordSquareWall<Wall>(walls, TILE_WALL, xoff, yoff);
    setTiledCoordSquareIntersect<Wall>(cycleWalls, mobspawners, TILE_MOB_SPAWNER, xoff, yoff);
    setTiledCoordSquareIntersect<Door>(doorWalls, doors, TILE_DOOR, xoff, yoff);

//    tiles lost because of the square pattern
    for (int i=0; i < maze.getWidth()-1;i++)
        for (int j=0; j < maze.getLength()-1;j++)
            tiles[squareID(2*i+1+xoff, 2*j+1+yoff, length)]->setTileType(TILE_WALL);
    if (externalWalls){
        for (int i=0; i < width; i++)
            for (int j=0; j < yoff; j++){
                tiles[squareID(i, j, length)]->setTileType(TILE_WALL);
                tiles[squareID(i, length-1-j, length)]->setTileType(TILE_WALL);
            }
        for (int i=0; i < xoff; i++)
            for (int j=yoff; j < length-yoff; j++){
                tiles[squareID(i, j, length)]->setTileType(TILE_WALL);
                tiles[squareID(width-1-i, j, length)]->setTileType(TILE_WALL);
            }
    }
}

void MazeTiled::setHexagonTiling(MazeWithWalls & maze, bool externalWalls){
    vector<Wall> walls = maze.getWalls();
    vector<Wall> cycleWalls = maze.getCycles();
    vector<Door> doorWalls = maze.getDoors();
    int xoff = 0, yoff = 0;
    if (externalWalls){
        xoff = 1;
        yoff = 2; //yoff must be pair
    }
    width = 2*maze.getWidth()+2*xoff;
    length = 2*maze.getLength()-1+2*yoff;
    int id = 0;
    for (int i=0; i < width; i++)
        for (int j=0; j < length; j++) {
            tiles.push_back(make_shared<TileHexagon>(TileHexagon(id,i,j)));
            id++;
        }

    setTiledCoordHexagonWall<Wall>(walls, TILE_WALL, xoff, yoff);
    setTiledCoordHexagonIntersect<Wall>(cycleWalls, mobspawners, TILE_MOB_SPAWNER, xoff, yoff);
    setTiledCoordHexagonIntersect<Door>(doorWalls, doors, TILE_DOOR, xoff, yoff);

//    tiles lost because of the hexagon pattern
    for (int j=yoff; j < length-yoff; j++){
        if ((j+2-yoff)%4 == 0){
            tiles[hexagonID(xoff, j, length)]->setTileType(TILE_VOID);
        } else {
            tiles[hexagonID(width-1-xoff, j, length)]->setTileType(TILE_VOID);
        }
    }
    if (externalWalls){
        for (int i=0; i < width; i++)
            for (int j=0; j < yoff; j++){
                tiles[hexagonID(i, j, length)]->setTileType(TILE_VOID);
                tiles[hexagonID(i, length-1-j, length)]->setTileType(TILE_VOID);
            }
        for (int i=0; i < xoff; i++)
            for (int j=yoff; j < length-yoff; j++){
                tiles[hexagonID(i, j, length)]->setTileType(TILE_VOID);
                tiles[hexagonID(width-1-i, j, length)]->setTileType(TILE_VOID);
            }
    }
}

template<typename T>
void MazeTiled::setTiledCoordTriangleWall(vector<T>& intersections, TileType tileType, int offset){
    for (unsigned int i = 0; i < intersections.size();i++){
        int x1 = intersections[i].getT1()->getX();
        int y1 = intersections[i].getT1()->getY();
        int x2 = intersections[i].getT2()->getX();
        int y2 = intersections[i].getT2()->getY();
        //Difference between intersections and tiles in the final pattern
        int xw, yw, xt, yt;
        if (y1%2 == 0) {
            xw = 2*x2; yw = 2*y2; xt = 2*x1; yt = 2*y1;
        } else {
            xw = 2*x1; yw = 2*y1; xt = 2*x2; yt = 2*y2;
        }
        if (xw > xt) {
            tiles[triangleID(xt+1+offset,yt+offset)]->setTileType(tileType);
            tiles[triangleID(xt+1+offset,yt+1+offset)]->setTileType(tileType);
            tiles[triangleID(xt+1+offset,yt+2+offset)]->setTileType(tileType);
        } else if (yw > yt) {
            tiles[triangleID(xt-1+offset,yt+offset)]->setTileType(tileType);
            tiles[triangleID(xt+offset,yt+1+offset)]->setTileType(tileType);
            tiles[triangleID(xt+offset,yt+2+offset)]->setTileType(tileType);
        } else {
            tiles[triangleID(xt-1+offset,yt-2+offset)]->setTileType(tileType);
            tiles[triangleID(xt+offset,yt-1+offset)]->setTileType(tileType);
            tiles[triangleID(xt+offset,yt-2+offset)]->setTileType(tileType);
        }
    }
}

template<typename T>
void MazeTiled::setTiledCoordSquareWall(vector<T>& intersections, TileType tileType, int xoff, int yoff){
    for (unsigned int i = 0; i < intersections.size();i++){
        int x1 = intersections[i].getT1()->getX();
        int y1 = intersections[i].getT1()->getY();
        int x2 = intersections[i].getT2()->getX();
        int y2 = intersections[i].getT2()->getY();
        tiles[squareID(x1+x2+xoff,y1+y2+yoff,length)]->setTileType(tileType);
    }
}

template<typename T>
void MazeTiled::setTiledCoordHexagonWall(vector<T>& intersections, TileType tileType, int xoff, int yoff){
    for (unsigned int i = 0; i < intersections.size();i++){
        int x1 = intersections[i].getT1()->getX();
        int y1 = intersections[i].getT1()->getY();
        int x2 = intersections[i].getT2()->getX();
        int y2 = intersections[i].getT2()->getY();
        if ((y1+y2+2)%4 == 0) {
            tiles[hexagonID(x1+x2+1+xoff,y1+y2+yoff,length)]->setTileType(tileType);
        } else {
            tiles[hexagonID(x1+x2+xoff,y1+y2+yoff,length)]->setTileType(tileType);
        }
    }
}

template<typename T>
void MazeTiled::setTiledCoordTriangleIntersect(vector<T>& intersections,
    vector<shared_ptr<Tile>>& intersectionTiles, TileType tileType1, TileType tileType2, int offset){
    for (unsigned int i = 0; i < intersections.size();i++){
        int x1 = intersections[i].getT1()->getX();
        int y1 = intersections[i].getT1()->getY();
        int x2 = intersections[i].getT2()->getX();
        int y2 = intersections[i].getT2()->getY();
        //Difference between intersections and tiles in the final pattern
        int xw, yw, xt, yt;
        if (y1%2 == 0) {
            xw = 2*x2; yw = 2*y2; xt = 2*x1; yt = 2*y1;
        }
        else {
            xw = 2*x1; yw = 2*y1; xt = 2*x2; yt = 2*y2;
        }
        if (xw > xt) {
            tiles[triangleID(xt+1+offset,yt+offset)]->setTileType(tileType1);
            tiles[triangleID(xt+1+offset,yt+1+offset)]->setTileType(tileType2);
            intersectionTiles.push_back(tiles[triangleID(xt+1+offset,yt+1+offset)]);
            tiles[triangleID(xt+1+offset,yt+2+offset)]->setTileType(tileType1);
        } else if (yw > yt) {
            tiles[triangleID(xt-1+offset,yt+offset)]->setTileType(tileType1);
            tiles[triangleID(xt+offset,yt+1+offset)]->setTileType(tileType2);
            intersectionTiles.push_back(tiles[triangleID(xt+offset,yt+1+offset)]);
            tiles[triangleID(xt+offset,yt+2+offset)]->setTileType(tileType1);
        } else {
            tiles[triangleID(xt-1+offset,yt-2+offset)]->setTileType(tileType1);
            tiles[triangleID(xt+offset,yt-1+offset)]->setTileType(tileType2);
            intersectionTiles.push_back(tiles[triangleID(xt+offset,yt-1+offset)]);
            tiles[triangleID(xt+offset,yt-2+offset)]->setTileType(tileType1);
        }
    }
}

template<typename T>
void MazeTiled::setTiledCoordSquareIntersect(vector<T>& intersections,
    vector<shared_ptr<Tile>>& intersectionTiles, TileType tileType, int xoff, int yoff){
    for (unsigned int i = 0; i < intersections.size();i++){
        int x1 = intersections[i].getT1()->getX();
        int y1 = intersections[i].getT1()->getY();
        int x2 = intersections[i].getT2()->getX();
        int y2 = intersections[i].getT2()->getY();
        tiles[squareID(x1+x2+xoff,y1+y2+yoff,length)]->setTileType(tileType);
        intersectionTiles.push_back(tiles[squareID(x1+x2+xoff,y1+y2+yoff,length)]);
    }
}

template<typename T>
void MazeTiled::setTiledCoordHexagonIntersect(vector<T>& intersections,
    vector<shared_ptr<Tile>>& intersectionTiles, TileType tileType, int xoff, int yoff){
    for (unsigned int i = 0; i < intersections.size();i++){
        int x1 = intersections[i].getT1()->getX();
        int y1 = intersections[i].getT1()->getY();
        int x2 = intersections[i].getT2()->getX();
        int y2 = intersections[i].getT2()->getY();
        if ((y1+y2+2)%4 == 0) {
            tiles[hexagonID(x1+x2+1+xoff,y1+y2+yoff,length)]->setTileType(tileType);
            intersectionTiles.push_back(tiles[hexagonID(x1+x2+1+xoff,y1+y2+yoff,length)]);
        } else {
            tiles[hexagonID(x1+x2+xoff,y1+y2+yoff,length)]->setTileType(tileType);
            intersectionTiles.push_back(tiles[hexagonID(x1+x2+xoff,y1+y2+yoff,length)]);
        }
    }
}

int MazeTiled::triangleID(int i, int j){return i*i + j;}
int MazeTiled::squareID(int i, int j, int l){return i*l + j;}
int MazeTiled::hexagonID(int i, int j, int l){return i*l + j;}

MazeTiled::~MazeTiled(){}

int MazeTiled::getWidth(){return width;}
int MazeTiled::getLength(){return length;}
MazeType MazeTiled::getType(){return type;}
vector<shared_ptr<Tile>> MazeTiled::getTiles(){return tiles;}

