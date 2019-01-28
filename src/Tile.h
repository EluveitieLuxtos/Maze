#ifndef TILE_H
#define TILE_H

#include <memory>
#include <vector>

using namespace std;

typedef struct {
    int x;
    int y;
} Coord;

typedef enum {
	TRIANGLE,
	SQUARE,
	HEXAGON,
	M1_SQUARES
} MazeType;

typedef enum {
	TILE_VOID,
	TILE_FLOOR,
	TILE_WALL,
	TILE_DOOR,
	TILE_MOB_SPAWNER,
	TILE_TELEPORT,
	TILE_DEPARTURE
} TileType;

class Tile{
    public:
        Tile();
        Tile(int idinit, int xinit, int yinit, TileType tinit = TILE_FLOOR);
        virtual ~Tile();

        virtual vector<int> getNeighbours(int w, int l){return vector<int>();};
        int hashcode();

        int getId();
        int getX();
        int getY();
        TileType getTileType();
        void setTileType(TileType tinit);
    protected:
        int id;
        int x; //horizontal coordinate of pattern
        int y; //vertical coordinate of pattern
        TileType tiletype;

        virtual int getPatternId(int x, int y, int length){return -1;};
        virtual vector<Coord> getPolygon(vector<int> lengths){return vector<Coord>();};
    private:
};

#endif // TILE_H
