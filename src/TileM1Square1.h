#ifndef TILE_M1_SQUARE1_H
#define TILE_M1_SQUARE1_H

#include "Tile.h"

using namespace std;

class TileM1Square1 : public Tile{
    public:
        TileM1Square1();
        TileM1Square1(int idinit, int xinit, int yinit, TileType tinit = TILE_FLOOR);
        virtual ~TileM1Square1();
        vector<int> getNeighbours(int w, int l);
    protected:
    private:
        int getPatternId(int x, int y, int length);
        vector<Coord> getPolygon(vector<int> lengths);
};

#endif // TILE_M1_SQUARE1_H
