#ifndef TILE_HEXAGON_H
#define TILE_HEXAGON_H

#include "Tile.h"

using namespace std;

class TileHexagon : public Tile{
    public:
        TileHexagon();
        TileHexagon(int idinit, int xinit, int yinit, TileType tinit = TILE_FLOOR);
        virtual ~TileHexagon();
        vector<int> getNeighbours(int w, int h);
    protected:
    private:
        int getPatternId(int x, int y, int length);
        vector<Coord> getPolygon(vector<int> lengths);
};

#endif // TILE_HEXAGON_H
