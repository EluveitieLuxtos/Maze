#include <vector>

#include "TileTriangle.h"

TileTriangle::TileTriangle(){}

TileTriangle::TileTriangle(int idinit, int xinit, int yinit, TileType tinit):Tile(idinit, xinit, yinit, tinit){};

TileTriangle::~TileTriangle(){}

vector<int> TileTriangle::getNeighbours(int w, int){
    vector<int> neighbours;

    if (y%2 == 0) {
        if (x < w - 2)
            neighbours.push_back(getPatternId(x+1,y+1,0));
        if (y > 0)
            neighbours.push_back(getPatternId(x,y-1,0));
        if (y < 2 * x)
            neighbours.push_back(getPatternId(x,y+1,0));
    } else {
        neighbours.push_back(getPatternId(x-1,y-1,0));
        neighbours.push_back(getPatternId(x,y-1,0));
        neighbours.push_back(getPatternId(x,y+1,0));
    }

    return neighbours;
}

int TileTriangle::getPatternId(int i, int j, int){
    return i*i + j;
}

vector<Coord> TileTriangle::getPolygon(vector<int> lengths){
    vector<Coord> polygon;

    return polygon;
}
