#ifndef DOOR_H
#define DOOR_H

#include <memory>

#include "Tile.h"

class Door{
    public:
        Door();
        Door(shared_ptr<Tile>& t1init, shared_ptr<Tile>& t2init);
        virtual ~Door();
        int hashcode();

        shared_ptr<Tile> getT1();
        shared_ptr<Tile> getT2();
    protected:
    private:
        shared_ptr<Tile> t1;
        shared_ptr<Tile> t2;
};

#endif // DOOR_H
