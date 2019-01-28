#include <vector>

#include "TileM1Square2.h"

TileM1Square2::TileM1Square2(){}

TileM1Square2::TileM1Square2(int idinit, int xinit, int yinit, TileType tinit)
    :Tile(idinit, xinit, yinit, tinit){};

TileM1Square2::~TileM1Square2(){}

vector<int> TileM1Square2::getNeighbours(int w, int l){
    //rectangular maze of width w and length l
    vector<int> neighbours;
    int patternRoot = 5*getPatternId(x,y,l);
    int idInPattern = id - patternRoot;
    switch (idInPattern) {
        case 1:
            neighbours.push_back(patternRoot);
            neighbours.push_back(patternRoot + 2);
            neighbours.push_back(patternRoot + 3);
            if (x>0)
                neighbours.push_back(5*getPatternId(x-1,y,l)+3);
            if (y>0) {
                neighbours.push_back(5*getPatternId(x,y-1,l)+2);
                neighbours.push_back(5*getPatternId(x,y-1,l)+4);
            }
            break;
        case 2:
            neighbours.push_back(patternRoot + 1);
            neighbours.push_back(patternRoot + 4);
            if (x>0) {
                neighbours.push_back(5*getPatternId(x-1,y,l)+3);
                neighbours.push_back(5*getPatternId(x-1,y,l)+4);
            }
            if (y<l-1) {
                neighbours.push_back(5*getPatternId(x,y+1,l));
                neighbours.push_back(5*getPatternId(x,y+1,l)+1);
            }
            break;
        case 3:
            neighbours.push_back(patternRoot + 1);
            neighbours.push_back(patternRoot + 4);
            if (x<w-1) {
                neighbours.push_back(5*getPatternId(x+1,y,l));
                neighbours.push_back(5*getPatternId(x+1,y,l)+1);
                neighbours.push_back(5*getPatternId(x+1,y,l)+2);
            }
            if (y>0)
                neighbours.push_back(5*getPatternId(x,y-1,l)+4);
            break;
        case 4:
            neighbours.push_back(patternRoot + 2);
            neighbours.push_back(patternRoot + 3);
            if (x<w-1) {
                neighbours.push_back(5*getPatternId(x+1,y,l)+2);
            }
            if (y<l-1) {
                neighbours.push_back(5*getPatternId(x,y+1,l)+1);
                neighbours.push_back(5*getPatternId(x,y+1,l)+3);
            }
            if (x<w-1 && y<l-1)
                neighbours.push_back(5*getPatternId(x+1,y+1,l));
            break;
        default:
            break;
    }

    return neighbours;
}

int TileM1Square2::getPatternId(int i, int j, int l){
    return i*l + j;
}

vector<Coord> TileM1Square2::getPolygon(vector<int> lengths){
    vector<Coord> polygon;

    return polygon;
}
