
#include "GameState.h"
#include "../GameObjects/Sprites/Bomber.h"
#include "../GameObjects/Sprites/AISprite.h"
#include "../../../Constants.h"

using namespace Bomber::Backend;
using namespace cocos2d;

GameState::GameState(unsigned int width, unsigned int height)
{
    _lastChangeId = 0;
    _lastChangeIdOffset = 0;

    _goalReached = false;

    _width = width;
    _height = height;

    _spriteLayer = new GameStateLayer<Sprite>("Sprite Layer", _width, _height);
    _obstacleLayer = new GameStateLayer<Obstacle>("Obstacles Layer", _width, _height);
    _bombLayer = new GameStateLayer<Bomb>("Bomb Layer", _width, _height);
    _portalLayer = new GameStateLayer<Portal>("Portal Layer", _width, _height);
    _portalExitLayer = new GameStateLayer<PortalExit>("Portal Exit Layer", _width, _height);
    _effectLayer = new GameStateLayer<Effect>("Effect Layer", _width, _height);
    _specialLayer = new GameStateLayer<GameObject>("Special Layer", _width, _height);
    _switchLayer = new GameStateLayer<Switch>("Trap Layer", _width, _height);
    _switchTargetLayer = new GameStateLayer<GameObject>("Trap Target Layer", _width, _height);
}

GameState::~GameState()
{

}

void GameState::init(TMXTiledMap *tiledMap)
{
    _tiledMap = tiledMap;
    
    Object *ccObject;

    // level properties

    auto properties = tiledMap->getProperties();
    auto propertiesKeys = properties->allKeys();

    CCARRAY_FOREACH(propertiesKeys, ccObject)
    {
        auto key = ((String *) ccObject)->getCString();
        auto value = properties->valueForKey(key)->intValue();

        if (strncmp("goal", key, 4) == 0)
        {
            if (strcmp(key, "goal_mobs_alive") == 0)
            {
                _goalConditions[CONDITION_MOBS_ALIVE] = value;
            }
        }
    }

    // obstacles

    unsigned int gid;
    TMXLayer *obstacleLayer = tiledMap->layerNamed("obstacles");

    for (unsigned iy = 0; iy < _height; iy++)
    {
        for (unsigned int ix = 0; ix < _width; ix++)
        {
            gid = obstacleLayer->tileGIDAt(ccp(ix, _height - 1 - iy));

            if (gid == 0)
                continue;
            
            Obstacle *obstacle = Obstacle::getInstanceByGid(gid);
            obstacle->setId(iy*_width + ix);
            obstacle->setPosition(ix*TILE_WIDTH, iy*TILE_HEIGHT);
            obstacle->setSize(TILE_WIDTH, TILE_HEIGHT);

            _obstacleLayer->addObject(obstacle);
        }
    }

    // sprites
    
    TMXLayer *spriteLayer = tiledMap->layerNamed("sprites");

    for (unsigned int iy = 0; iy < _height; iy++)
    {
        for (unsigned int ix = 0; ix < _width; ix++)
        {
            gid = spriteLayer->tileGIDAt(ccp(ix, _height - 1 - iy));

            if (gid == 0)
                continue;
            
            Sprite *sprite = Sprite::getInstanceByGid(gid);
            sprite->setId(iy*_width + ix);
            sprite->setPosition(ix*TILE_WIDTH, iy*TILE_HEIGHT);
            sprite->setSize(TILE_WIDTH, TILE_HEIGHT);

            _spriteLayer->addObject(sprite);
        }
    }

    TMXLayer *spriteToSpawnLayer = tiledMap->layerNamed("sprites2spawn");

    for (unsigned int iy = 0; iy < _height; iy++)
    {
        for (unsigned int ix = 0; ix < _width; ix++)
        {
            gid = spriteToSpawnLayer->tileGIDAt(ccp(ix, _height - 1 - iy));

            if (gid == 0)
                continue;
            
            Sprite *sprite = Sprite::getInstanceByGid(gid);
            sprite->setId(iy*_width + ix);
            sprite->setPosition(ix*TILE_WIDTH, iy*TILE_HEIGHT);
            sprite->setSize(TILE_WIDTH, TILE_HEIGHT);
            sprite->setActive(false);

            _spriteLayer->addObject(sprite);
        }
    }

    // effects
    
    TMXLayer *effectLayer = tiledMap->layerNamed("effects");

    for (unsigned int iy = 0; iy < _height; iy++)
    {
        for (unsigned int ix = 0; ix < _width; ix++)
        {
            gid = effectLayer->tileGIDAt(ccp(ix, _height - 1 - iy));

            if (gid == 0)
                continue;

            Effect *effect = Effect::getInstanceByGid(gid);
            effect->setId(iy*_width + ix);
            effect->setPosition(ix*TILE_WIDTH, iy*TILE_HEIGHT);
            effect->setSize(TILE_WIDTH, TILE_HEIGHT);

            _effectLayer->addObject(effect);
        }
    }    
    
    TMXLayer *effectToSpawnLayer = tiledMap->layerNamed("effects2spawn");

    for (unsigned int iy = 0; iy < _height; iy++)
    {
        for (unsigned int ix = 0; ix < _width; ix++)
        {
            gid = effectToSpawnLayer->tileGIDAt(ccp(ix, _height - 1 - iy));

            if (gid == 0)
                continue;

            Effect *effect = Effect::getInstanceByGid(gid);
            effect->setId(iy*_width + ix);
            effect->setPosition(ix*TILE_WIDTH, iy*TILE_HEIGHT);
            effect->setSize(TILE_WIDTH, TILE_HEIGHT);
            effect->setActive(false);

            _effectLayer->addObject(effect);
        }
    }

    int id, x, y, width, height;
    Dictionary *dict;
    TMXObjectGroup *objectGroup;

    // portals

    objectGroup = tiledMap->objectGroupNamed("portals");
    Array *portals = objectGroup->getObjects();

    CCARRAY_FOREACH(portals, ccObject)
    {
        dict = (Dictionary*) ccObject;

        id = ((String*) dict->objectForKey("name"))->intValue();
        x = ((String*) dict->objectForKey("x"))->intValue();
        y = ((String*) dict->objectForKey("y"))->intValue();
        width = ((String*) dict->objectForKey("width"))->intValue();
        height = ((String*) dict->objectForKey("height"))->intValue();

        int top =  ((String*) dict->objectForKey("top"))->intValue();
        int bottom =  ((String*) dict->objectForKey("bottom"))->intValue();
        int left =  ((String*) dict->objectForKey("left"))->intValue();
        int right =  ((String*) dict->objectForKey("right"))->intValue();

        Portal *portal = new Portal();
        portal->setId(id);
        portal->setPosition(x - (x % TILE_WIDTH), y - (y % TILE_HEIGHT));
        portal->setSize(TILE_WIDTH, TILE_HEIGHT);
        portal->configure(top, bottom, left, right);

        _portalLayer->addObject(portal);
    }

    objectGroup = tiledMap->objectGroupNamed("portal_exits");
    Array *portalExits = objectGroup->getObjects();

    CCARRAY_FOREACH(portalExits, ccObject)
    {
        dict = (Dictionary*) ccObject;
        
        id = ((String*) dict->objectForKey("name"))->intValue();
        x = ((String*) dict->objectForKey("x"))->intValue();
        y = ((String*) dict->objectForKey("y"))->intValue();
        width = ((String*) dict->objectForKey("width"))->intValue();
        height = ((String*) dict->objectForKey("height"))->intValue();   

        PortalExit *portalExit = new PortalExit();
        portalExit->setId(id);
        portalExit->setPosition(x - (x % TILE_WIDTH), y - (y % TILE_HEIGHT));
        portalExit->setSize(TILE_WIDTH, TILE_HEIGHT);

        _portalExitLayer->addObject(portalExit);
    }

    // switches

    objectGroup = tiledMap->objectGroupNamed("switches");
    Array *switches = objectGroup->getObjects();

    CCARRAY_FOREACH(switches, ccObject)
    {
        dict = (Dictionary*) ccObject;

        id = ((String*) dict->objectForKey("name"))->intValue();
        x = ((String*) dict->objectForKey("x"))->intValue();
        y = ((String*) dict->objectForKey("y"))->intValue();
        width = ((String*) dict->objectForKey("width"))->intValue();
        height = ((String*) dict->objectForKey("height"))->intValue();
        
        bool oneTime = ((String*) dict->objectForKey("one_time"))->boolValue();
        bool bombSensitive = ((String*) dict->objectForKey("bomb_sensitive"))->boolValue();
        bool passingSensitive = ((String*) dict->objectForKey("passing_sensitive"))->boolValue();

        Switch *switchObject = new Switch();
        switchObject->setId(id);
        switchObject->setPosition(x, y);
        switchObject->setSize(width, height);

        switchObject->setOneTime(oneTime);
        switchObject->setBombSensitive(bombSensitive);
        switchObject->setPassingSensitive(passingSensitive);

        _switchLayer->addObject(switchObject);
    }

    objectGroup = tiledMap->objectGroupNamed("switch_targets");
    Array *switchTargets = objectGroup->getObjects();

    CCARRAY_FOREACH(switchTargets, ccObject)
    {
        dict = (Dictionary*) ccObject;

        id = ((String*) dict->objectForKey("name"))->intValue();
        x = ((String*) dict->objectForKey("x"))->intValue();
        y = ((String*) dict->objectForKey("y"))->intValue();
        width = ((String*) dict->objectForKey("width"))->intValue();
        height = ((String*) dict->objectForKey("height"))->intValue();         

        GameObject *switchTarget = new GameObject();
        switchTarget->setId(id);
        switchTarget->setPosition(x, y);
        switchTarget->setSize(width, height);

        _switchTargetLayer->addObject(switchTarget);
    }
}

void GameState::reset()
{
    _changes.clear();
    _lastChangeId = 0;
    _lastChangeIdOffset = 0;
    _goalReached = false;

    _spriteLayer->reset();
    _obstacleLayer->reset();
    _bombLayer->reset();
    _portalLayer->reset();
    _portalExitLayer->reset();
    _effectLayer->reset();
    _specialLayer->reset();
    _switchLayer->reset();
    _switchTargetLayer->reset();

    _goalConditions.clear();

    this->init(_tiledMap);
}

std::pair< unsigned int, std::vector<GameStateChange *> > GameState::getChangesFromId(unsigned int id)
{
    std::vector<GameStateChange *> changes;

    unsigned int fromId = id - _lastChangeIdOffset;
    unsigned int toId = _lastChangeId - _lastChangeIdOffset;

    for (unsigned int i = fromId; i < toId; i++) 
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

