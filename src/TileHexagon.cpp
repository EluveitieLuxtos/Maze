#include <vector>

#include "TileHexagon.h"

TileHexagon::TileHexagon(){}

TileHexagon::TileHexagon(int idinit, int xinit, int yinit, TileType tinit):Tile(idinit, xinit, yinit, tinit){};

TileHexagon::~TileHexagon(){}

vector<int> TileHexagon::getNeighbours(int w, int l){
    //rectangular maze of width w and length l
    vector<int> neighbours;

    if (x > 0)
        neighbours.push_back(getPatternId(x-1,y,l));
    if (x < w - 1)
        neighbours.push_back(getPatternId(x+1,y,l));
    if (y > 0)
        neighbours.push_back(getPatternId(x,y-1,l));
    if (y < l - 1)
        neighbours.push_back(getPatternId(x,y+1,l));
    if (y%2 == 0) {
        if (x > 0) {
            if (y > 0)
                neighbours.push_back(getPatternId(x-1,y-1,l));
            if (y < l - 1)
                neighbours.push_back(getPatternId(x-1,y+1,l));
        }
    } else {
        if (x < w - 1) {
            if (y > 0)
                neighbours.push_back(getPatternId(x+1,y-1,l));
            if (y < l - 1)
                neighbours.push_back(getPatternId(x+1,y+1,l));
        }
    }

    return neighbours;
}

int TileHexagon::getPatternId(int i, int j, int l){
    return i*l + j;
}

vector<Coord> TileHexagon::getPolygon(vector<int> lengths){
    vector<Coord> polygon;

    return polygon;
}
