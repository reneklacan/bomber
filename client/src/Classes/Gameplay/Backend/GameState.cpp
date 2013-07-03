
#include "GameState.h"
#include "Bomber.h"
#include "AISprite.h"
#include "../../Constants.h"

using namespace Bomber::Backend;
using namespace cocos2d;

GameState::GameState(unsigned int width, unsigned int height)
{
    _lastChangeId = 0;
    _lastChangeIdOffset = 0;

    _width = width;
    _height = height;

    _spriteLayer = new GameStateLayer<Sprite>("Sprite Layer", _width, _height);
    _obstacleLayer = new GameStateLayer<Obstacle>("Obstacles Layer", _width, _height);
    _bombLayer = new GameStateLayer<Bomb>("Bomb Layer", _width, _height);
    _portalLayer = new GameStateLayer<Portal>("Portal Layer", _width, _height);
    _portalExitLayer = new GameStateLayer<PortalExit>("Portal Exit Layer", _width, _height);
    _effectLayer = new GameStateLayer<Effect>("Effect Layer", _width, _height);
    _specialLayer = new GameStateLayer<GameObject>("Special Layer", _width, _height);
}

GameState::~GameState()
{

}

void GameState::init(TMXTiledMap *tiledMap)
{
    unsigned int gid;
    TMXLayer *obstacleLayer = tiledMap->layerNamed("obstacles");

    for (int iy = 0; iy < _height; iy++)
    {
        for (int ix = 0; ix < _width; ix++)
        {
            gid = obstacleLayer->tileGIDAt(ccp(ix, _height - 1 - iy));

            if (gid == 0)
                continue;

            Obstacle *obstacle = new Obstacle();
            obstacle->setId(iy*_width + ix);
            obstacle->setPosition(ix*TILE_WIDTH, iy*TILE_HEIGHT);
            obstacle->setSize(TILE_WIDTH, TILE_HEIGHT);
            obstacle->configureFromGid(gid);

            _obstacleLayer->addObject(obstacle);
        }
    }

    TMXLayer *spriteLayer = tiledMap->layerNamed("sprites");

    for (int iy = 0; iy < _height; iy++)
    {
        for (int ix = 0; ix < _width; ix++)
        {
            gid = spriteLayer->tileGIDAt(ccp(ix, _height - 1 - iy));

            if (gid == 0)
                continue;

            Sprite *sprite= new AISprite();
            sprite->setId(iy*_width + ix);
            sprite->setPosition(ix*TILE_WIDTH, iy*TILE_HEIGHT);
            sprite->setSize(TILE_WIDTH, TILE_HEIGHT);
            sprite->configureFromGid(gid);

            _spriteLayer->addObject(sprite);
        }
    }

    int id, x, y, width, height;
    Object *ccObject;
    Dictionary *dict;
    TMXObjectGroup *objectGroup;

    objectGroup = tiledMap->objectGroupNamed("portals");
    Array *portals = objectGroup->getObjects();

    CCARRAY_FOREACH(portals, ccObject)
    {
        dict = (Dictionary*) ccObject;

        id = ((String*)dict->objectForKey("name"))->intValue();
        x = ((String*)dict->objectForKey("x"))->intValue();
        y = ((String*)dict->objectForKey("y"))->intValue();
        width = ((String*)dict->objectForKey("width"))->intValue();
        height = ((String*)dict->objectForKey("height"))->intValue();

        Portal *portal = new Portal();
        portal->setId(id);
        portal->setPosition(x, y);
        portal->setSize(width, height);

        _portalLayer->addObject(portal);
    }

    objectGroup = tiledMap->objectGroupNamed("portal_exits");
    Array *portalExits = objectGroup->getObjects();

    CCARRAY_FOREACH(portalExits, ccObject)
    {
        dict = (Dictionary*) ccObject;

        id = ((String*)dict->objectForKey("name"))->intValue();
        x = ((String*)dict->objectForKey("x"))->intValue();
        y = ((String*)dict->objectForKey("y"))->intValue();
        width = ((String*)dict->objectForKey("width"))->intValue();
        height = ((String*)dict->objectForKey("height"))->intValue();         

        PortalExit *portalExit = new PortalExit();
        portalExit->setId(id);
        portalExit->setPosition(x, y);
        portalExit->setSize(width, height);

        _portalExitLayer->addObject(portalExit);
    }
}

std::pair< unsigned int, std::vector<GameStateChange *> > GameState::getChangesFromId(unsigned int id)
{
    std::vector<GameStateChange *> changes;

    unsigned int fromId = id - _lastChangeIdOffset;
    unsigned int toId = _lastChangeId - _lastChangeIdOffset;

    for (int i = fromId; i < toId; i++) 
    {
        changes.push_back(_changes[i]);
    }

    return std::pair< unsigned int, std::vector<GameStateChange *> >(_lastChangeId, changes);
}

void GameState::deleteChangesToId(unsigned int id)
{
    unsigned int numberToDelete = id - _lastChangeIdOffset;

    for (unsigned int i = 0; i < numberToDelete; i++)
    {
        _changes.pop_front();
        _lastChangeIdOffset++;
    }
}

void GameState::addChange(GameStateChange *change)
{
    _lastChangeId += 1;
    _changes.push_back(change);
}

