#include "Tile.h"

Tile::Tile(){}

Tile::Tile(int idinit, int xinit, int yinit, TileType tinit)
    :id(idinit), x(xinit), y(yinit), tiletype(tinit){
}

Tile::~Tile(){}

int Tile::hashcode(){return id;}

int Tile::getId(){return id;}

int Tile::getX(){return x;}

int Tile::getY(){return y;}

TileType Tile::getTileType(){return tiletype;}
void Tile::setTileType(TileType tinit){tiletype = tinit;}


