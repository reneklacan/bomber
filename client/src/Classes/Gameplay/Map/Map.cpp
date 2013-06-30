#include "Map.h"
#include "Bomb.h"
#include "../../Constants.h"

Map::Map()
{
}

Map::~Map()
{
}

//
bool Map::init()
{
    if (!CCLayer::init())
        return false;

    _tiledMap = CCTMXTiledMap::create("tiles/level_name.tmx");
    this->addChild(_tiledMap, 0, 7);
    _tiledMap->setPosition(ccp(0, 0));

    CCSize mapSize = _tiledMap->getMapSize();
    _width = (int) mapSize.width;
    _height = (int) mapSize.height;

    return true;
}

//
void Map::addToPosition(CCPoint point)
{
    this->setPosition(ccpAdd(this->getPosition(), point));
}

//
void Map::addBomb(unsigned int key, CCObject* bomb)
{
    _spawnedBombs[key] = bomb;
}

//
CCObject *Map::getBomb(unsigned int key)
{
    return _spawnedBombs[key];
}

//
void Map::removeBomb(unsigned int key)
{
    _spawnedBombs.erase(key);
}
