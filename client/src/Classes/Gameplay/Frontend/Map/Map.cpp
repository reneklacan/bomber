#include "Map.h"
#include "Bomb.h"
#include "../../../Constants.h"

Map::Map()
{
}

Map::~Map()
{
}

//
bool Map::init()
{
    if (!Layer::init())
        return false;

    _tiledMap = TMXTiledMap::create("tiles/level_name.tmx");
    this->addChild(_tiledMap, 0, 7);
    _tiledMap->setPosition(ccp(0, 0));

    Size mapSize = _tiledMap->getMapSize();
    _width = (int) mapSize.width;
    _height = (int) mapSize.height;

    return true;
}

//
void Map::addToPosition(Point point)
{
    this->setPosition(ccpAdd(this->getPosition(), point));
}

//
void Map::addBomb(unsigned int key, Object* bomb)
{
    _spawnedBombs[key] = bomb;
}

//
Object *Map::getBomb(unsigned int key)
{
    return _spawnedBombs[key];
}

//
void Map::removeBomb(unsigned int key)
{
    _spawnedBombs.erase(key);
}
