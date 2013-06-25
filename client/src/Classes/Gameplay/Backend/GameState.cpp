
#include "GameState.h"
#include "Obstacle.h"
#include "Portal.h"
#include "PortalExit.h"
#include "../../Constants.h"

using namespace Bomber::Backend;

GameState::GameState(unsigned int width, unsigned int height)
{
    _lastChangeId = 0;
    _lastChangeIdOffset = 0;

    _width = width;
    _height = height;

    _spriteLayer = new GameStateLayer(_width, _height);
    _obstacleLayer = new GameStateLayer(_width, _height);
    _portalLayer = new GameStateLayer(_width, _height);
    _portalExitLayer = new GameStateLayer(_width, _height);
    _specialLayer = new GameStateLayer(_width, _height);
    _bombLayer = new GameStateLayer(_width, _height);

    GameStateLayer *layers[] = {
        _spriteLayer,
        _obstacleLayer,
        _portalLayer,
        _portalExitLayer,
        _specialLayer,
        _bombLayer
    };

    _allLayers.insert(
            _allLayers.begin(),
            layers,
            layers + sizeof(layers)/sizeof(layers[0])
    );
}

GameState::~GameState()
{

}

void GameState::init(CCTMXTiledMap *tiledMap)
{
    CCTMXLayer *obstaclesLayer = tiledMap->layerNamed("obstacles");

    for (int iy = 0; iy < _height; iy++)
    {
        for (int ix = 0; ix < _width; ix++)
        {
            if (!obstaclesLayer->tileGIDAt(ccp(ix, _height - 1 - iy)))
                continue;

            Obstacle *obstacle = new Obstacle();
            obstacle->setId(iy*_width + ix);
            obstacle->setPosition(ix*TILE_WIDTH, iy*TILE_HEIGHT);
            obstacle->setSize(TILE_WIDTH, TILE_HEIGHT);

            _obstacleLayer->addObject(obstacle);
        }
    }

    int id, x, y, width, height;
    CCObject *ccObject;
    CCDictionary *dict;
    CCTMXObjectGroup *objectGroup;

    objectGroup = tiledMap->objectGroupNamed("portals");
    CCArray *portals = objectGroup->getObjects();

    CCARRAY_FOREACH(portals, ccObject)
    {
        dict = (CCDictionary*) ccObject;

        id = ((CCString*)dict->objectForKey("name"))->intValue();
        x = ((CCString*)dict->objectForKey("x"))->intValue();
        y = ((CCString*)dict->objectForKey("y"))->intValue();
        width = ((CCString*)dict->objectForKey("width"))->intValue();
        height = ((CCString*)dict->objectForKey("height"))->intValue();

        Portal *portal = new Portal();
        portal->setId(id);
        portal->setPosition(x, y);
        portal->setSize(width, height);

        _portalLayer->addObject(portal);
    }

    objectGroup = tiledMap->objectGroupNamed("portal_exits");
    CCArray *portalExits = objectGroup->getObjects();

    CCARRAY_FOREACH(portalExits, ccObject)
    {
        dict = (CCDictionary*) ccObject;

        id = ((CCString*)dict->objectForKey("name"))->intValue();
        x = ((CCString*)dict->objectForKey("x"))->intValue();
        y = ((CCString*)dict->objectForKey("y"))->intValue();
        width = ((CCString*)dict->objectForKey("width"))->intValue();
        height = ((CCString*)dict->objectForKey("height"))->intValue();         

        PortalExit *portalExit = new PortalExit();
        portalExit->setId(id);
        portalExit->setPosition(x, y);
        portalExit->setSize(width, height);

        _portalExitLayer->addObject(portalExit);
    }
}

std::vector<GameStateChange *> GameState::getChangesFromId(unsigned int id)
{
    std::vector<GameStateChange *> changes;

    unsigned int fromId = id - _lastChangeIdOffset;
    unsigned int toId = _lastChangeId - _lastChangeIdOffset;

    for (int i = fromId; i < toId; i++) 
    {
        changes.push_back(_changes[i]);
    }

    return changes;
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

