#ifndef TILE_SQUARE_H
#define TILE_SQUARE_H

#include "Tile.h"

using namespace std;

class TileSquare : public Tile{
    public:
        TileSquare();
        TileSquare(int idinit, int xinit, int yinit, TileType tinit = TILE_FLOOR);
        virtual ~TileSquare();
        vector<int> getNeighbours(int w, int l);
    protected:
    private:
        int getPatternId(int x, int y, int length);
        vector<Coord> getPolygon(vector<int> lengths);
};

#endif // TILE_SQUARE_H
