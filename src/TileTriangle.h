#ifndef TILE_TRIANGLE_H
#define TILE_TRIANGLE_H

#include "Tile.h"

using namespace std;

class TileTriangle : public Tile{
    public:
        TileTriangle();
        TileTriangle(int idinit, int xinit, int yinit, TileType tinit = TILE_FLOOR);
        virtual ~TileTriangle();
        vector<int> getNeighbours(int w, int);
    protected:
    private:
        int getPatternId(int x, int y, int length);
        vector<Coord> getPolygon(vector<int> lengths);
};

#endif // TILE_TRIANGLE_H
