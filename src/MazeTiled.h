#ifndef MAZE_TILED_H
#define MAZE_TILED_H

#include <memory>
#include <vector>

#include "MazeWithWalls.h"
#include "Tile.h"

using namespace std;

class MazeTiled {
    public:
        MazeTiled();
        MazeTiled(MazeType type, int width, int cyclesNumber, bool externalWalls = true);
        MazeTiled(MazeType type, int width, int length, int cyclesNumber, int setsNumber = 1, bool externalWalls = true);
        virtual ~MazeTiled();

        int triangleID(int i, int j);
        int squareID(int i, int j, int l);
        int hexagonID(int i, int j, int l);

        MazeType getType();
        int getWidth();
        int getLength();
        vector<shared_ptr<Tile>> getTiles();
        bool isObstacle(int x, int y);
    protected:
        MazeType type;
        int width;
        int length;
        vector<shared_ptr<Tile>> tiles;
        vector<shared_ptr<Tile>> mobspawners;
        vector<shared_ptr<Tile>> doors;
    private:
        void setTiling(MazeWithWalls& maze, bool externalWalls);
        void setTriangleTiling(MazeWithWalls & maze, bool externalWalls);
        void setSquareTiling(MazeWithWalls & maze, bool externalWalls);
        void setHexagonTiling(MazeWithWalls & maze, bool externalWalls);
        template<typename T>
        void setTiledCoordTriangleWall(vector<T>& intersections, TileType tileType, int offset);
        template<typename T>
        void setTiledCoordSquareWall(vector<T>& intersections, TileType tileType, int xoff, int yoff);
        template<typename T>
        void setTiledCoordHexagonWall(vector<T>& intersections, TileType tileType, int xoff, int yoff);
        template<typename T>
        void setTiledCoordTriangleIntersect(vector<T>& intersections,
            vector<shared_ptr<Tile>>& intersectionTiles, TileType tileType1, TileType tileType2, int offset);
        template<typename T>
        void setTiledCoordSquareIntersect(vector<T>& intersections,
            vector<shared_ptr<Tile>>& intersectionTiles, TileType tileType, int xoff, int yoff);
        template<typename T>
        void setTiledCoordHexagonIntersect(vector<T>& intersections,
            vector<shared_ptr<Tile>>& intersectionTiles, TileType tileType, int xoff, int yoff);
};

#endif // MAZE_TILED_H
