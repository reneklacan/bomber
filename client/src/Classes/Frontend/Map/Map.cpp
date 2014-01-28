#include "Map.h"
#include "../../Constants.h"
#include "../Primitives/MenuHelper.h"

//
bool Map::init()
{
    if (!Layer::init())
        return false;

    // create level name with appropriate path
    std::string levelPath = "levels/";
    levelPath += Bomber::Frontend::MenuSelections::getInstance()->getLevelFilename();

    _tiledMap = TMXTiledMap::create( levelPath.c_str() );
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
