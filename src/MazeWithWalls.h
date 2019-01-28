#ifndef MAZE_WITH_WALLS_H
#define MAZE_WITH_WALLS_H

#include <memory>
#include <map>
#include <vector>

#include "Door.h"
#include "Tile.h"
#include "Wall.h"

using namespace std;

class MazeWithWalls{
    public:
        MazeWithWalls();
        MazeWithWalls(MazeType type, int width, int cyclesNumber);
        MazeWithWalls(MazeType type, int width, int length, int cyclesNumber, int setsNumber = 1);
        virtual ~MazeWithWalls();

        MazeType getType();
        int getWidth();
        int getLength();
        vector<shared_ptr<Tile>> getTiles();
        vector<Wall> getWalls();
        vector<Wall> getCycles();
        vector<Door> getDoors();
    protected:
        MazeType type;
        int width; //number of horizontal patterns
        int length; //number of vertical patterns
        vector<shared_ptr<Tile>> tiles;
        vector<Wall> walls;
        vector<Wall> cycles;
        vector<Door> doors;
    private:
        void createTiling(); //only method to modify to add new tiling
        void createWalls();
        void pathMergingMethod(int setsNumber, int cyclesNumber);
};

#endif // MAZE_WITH_WALLS_H
