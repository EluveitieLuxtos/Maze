#include <vector>

#include "TileSquare.h"

TileSquare::TileSquare(){}

TileSquare::TileSquare(int idinit, int xinit, int yinit, TileType tinit):Tile(idinit, xinit, yinit, tinit){};

TileSquare::~TileSquare(){}

vector<int> TileSquare::getNeighbours(int w, int l){
    //rectangular maze of width w and length l
    vector<int> neighbours;
    if (x>0)
        neighbours.push_back(getPatternId(x-1,y,l));
    if (x<w-1)
        neighbours.push_back(getPatternId(x+1,y,l));
    if (y>0)
        neighbours.push_back(getPatternId(x,y-1,l));
    if (y<l-1)
        neighbours.push_back(getPatternId(x,y+1,l));

    return neighbours;
}

int TileSquare::getPatternId(int i, int j, int l){
    return i*l + j;
}

vector<Coord> TileSquare::getPolygon(vector<int> lengths){
    vector<Coord> polygon;

    return polygon;
}
