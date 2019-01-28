#include "Door.h"

Door::Door(){}

Door::Door(shared_ptr<Tile>& t1init, shared_ptr<Tile>& t2init)
    :t1(t1init), t2(t2init){}

Door::~Door(){}

int Door::hashcode(){
    //Symetric hashcode, to verify pairs of tiles
    return t1->hashcode() + t2 -> hashcode();
}

shared_ptr<Tile> Door::getT1(){return shared_ptr<Tile>(t1);}

shared_ptr<Tile> Door::getT2(){return shared_ptr<Tile>(t2);}
