#include <vector>

#include "TileM1Square1.h"

TileM1Square1::TileM1Square1(){}

TileM1Square1::TileM1Square1(int idinit, int xinit, int yinit, TileType tinit)
    :Tile(idinit, xinit, yinit, tinit){};

TileM1Square1::~TileM1Square1(){}

vector<int> TileM1Square1::getNeighbours(int w, int l){
    //rectangular maze of width w and length l
    vector<int> neighbours;
    neighbours.push_back(5*getPatternId(x,y,l)+1);
    if (x>0)
        neighbours.push_back(5*getPatternId(x-1,y,l)+3);
    if (y>0)
        neighbours.push_back(5*getPatternId(x,y-1,l)+2);
    if (x>0 && y>0)
        neighbours.push_back(5*getPatternId(x-1,y-1,l)+4);

    return neighbours;
}

int TileM1Square1::getPatternId(int i, int j, int l){
    return i*l + j;
}

vector<Coord> TileM1Square1::getPolygon(vector<int> lengths){
    vector<Coord> polygon;

    return polygon;
}
