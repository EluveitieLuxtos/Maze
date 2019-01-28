#ifndef TILE_M1_SQUARE2_H
#define TILE_M1_SQUARE2_H

#include "Tile.h"

using namespace std;

class TileM1Square2 : public Tile{
    public:
        TileM1Square2();
        TileM1Square2(int idinit, int xinit, int yinit, TileType tinit = TILE_FLOOR);
        virtual ~TileM1Square2();
        vector<int> getNeighbours(int w, int l);
    protected:
    private:
        int getPatternId(int x, int y, int length);
        vector<Coord> getPolygon(vector<int> lengths);
};

#endif // TILE_M1_SQUARE2_H
