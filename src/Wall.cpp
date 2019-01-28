#include "Wall.h"

Wall::Wall(){}

Wall::Wall(shared_ptr<Tile>& t1init, shared_ptr<Tile>& t2init)
    :t1(t1init), t2(t2init){}

Wall::~Wall(){}

int Wall::hashcode(){
    //Symetric hashcode, to verify pairs of tiles
    int h1 = t1->hashcode();
    int h2 = t2->hashcode();
    int hmax = max(h1, h2);
    int hmin = min(h1, h2);
    return (hmax*(hmax+1)/2+hmin);
}

shared_ptr<Tile> Wall::getT1(){return shared_ptr<Tile>(t1);}

shared_ptr<Tile> Wall::getT2(){return shared_ptr<Tile>(t2);}
