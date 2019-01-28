#ifndef WALL_H
#define WALL_H

#include <memory>

#include "Tile.h"

class Wall{
    public:
        Wall();
        Wall(shared_ptr<Tile>& t1init, shared_ptr<Tile>& t2init);
        virtual ~Wall();
        int hashcode();

        shared_ptr<Tile> getT1();
        shared_ptr<Tile> getT2();
    protected:
    private:
        shared_ptr<Tile> t1;
        shared_ptr<Tile> t2;
};

#endif // WALL_H
