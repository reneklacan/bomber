
#include "GameState.h"
#include "../../Backend/GameObjects/Sprites/Bomber.h"
#include "../../Backend/GameObjects/Sprites/AISprite.h"
#include "../../Constants.h"
#include "../Cache/ObjectCache.h"

using namespace Bomber::Common;
using namespace Bomber::Backend;

GameState::GameState(unsigned int width, unsigned int height)
{
    _lastChangeId = 0;
    _lastChangeIdOffset = 0;

    _goalReached = false;

    _spawnPoint.first = SPRITE_DEFAULT_SPAWN_X;
    _spawnPoint.second = SPRITE_DEFAULT_SPAWN_Y;

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

void GameState::init(cocos2d::TMXTiledMap *tiledMap)
{
    ObjectCache::getInstance()->reset();

    _tiledMap = tiledMap;
    
    cocos2d::Object *ccObject;

    // level properties

    auto properties = tiledMap->getProperties();
    auto propertiesKeys = properties->allKeys();

    CCARRAY_FOREACH(propertiesKeys, ccObject)
    {
        auto key = ((cocos2d::String *) ccObject)->getCString();
        auto value = properties->valueForKey(key)->intValue();

        if (strncmp("goal", key, 4) == 0)
        {
            if (strcmp(key, "goal_mobs_alive") == 0)
                _goalConditions[CONDITION_MOBS_ALIVE] = value;
            else if (strcmp(key, "goal_level_keys") == 0)
                _goalConditions[CONDITION_LEVEL_KEYS] = value;
        }
    }

    // obstacles

    unsigned int gid;
    cocos2d::TMXLayer *obstacleLayer = tiledMap->layerNamed("obstacles");

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
    
    cocos2d::TMXLayer *spriteLayer = tiledMap->layerNamed("sprites");

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

    cocos2d::TMXLayer *spriteToSpawnLayer = tiledMap->layerNamed("sprites2spawn");

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
    
    cocos2d::TMXLayer *effectLayer = tiledMap->layerNamed("effects");

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
    
    cocos2d::TMXLayer *effectToSpawnLayer = tiledMap->layerNamed("effects2spawn");

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
    cocos2d::Dictionary *dict;
    cocos2d::TMXObjectGroup *objectGroup;

    // portals

    objectGroup = tiledMap->objectGroupNamed("portals");
    cocos2d::Array *portals = objectGroup->getObjects();

    CCARRAY_FOREACH(portals, ccObject)
    {
        dict = (cocos2d::Dictionary*) ccObject;

        id = ((cocos2d::String*) dict->objectForKey("name"))->intValue();
        x = ((cocos2d::String*) dict->objectForKey("x"))->intValue();
        y = ((cocos2d::String*) dict->objectForKey("y"))->intValue();
        width = ((cocos2d::String*) dict->objectForKey("width"))->intValue();
        height = ((cocos2d::String*) dict->objectForKey("height"))->intValue();

        int top =  ((cocos2d::String*) dict->objectForKey("top"))->intValue();
        int bottom =  ((cocos2d::String*) dict->objectForKey("bottom"))->intValue();
        int left =  ((cocos2d::String*) dict->objectForKey("left"))->intValue();
        int right =  ((cocos2d::String*) dict->objectForKey("right"))->intValue();
        
        Portal *portal = (Portal *) ObjectCache::getInstance()->getObject(COT_PORTAL);
        portal->setId(id);
        portal->setPosition(x - (x % TILE_WIDTH), y - (y % TILE_HEIGHT));
        portal->setSize(TILE_WIDTH, TILE_HEIGHT);
        portal->configure(top, bottom, left, right);

        _portalLayer->addObject(portal);
    }

    objectGroup = tiledMap->objectGroupNamed("portal_exits");
    cocos2d::Array *portalExits = objectGroup->getObjects();

    CCARRAY_FOREACH(portalExits, ccObject)
    {
        dict = (cocos2d::Dictionary*) ccObject;
        
        id = ((cocos2d::String*) dict->objectForKey("name"))->intValue();
        x = ((cocos2d::String*) dict->objectForKey("x"))->intValue();
        y = ((cocos2d::String*) dict->objectForKey("y"))->intValue();
        width = ((cocos2d::String*) dict->objectForKey("width"))->intValue();
        height = ((cocos2d::String*) dict->objectForKey("height"))->intValue();   
        
        PortalExit *portalExit = (PortalExit *) ObjectCache::getInstance()->getObject(COT_PORTAL_EXIT);
        portalExit->setId(id);
        portalExit->setPosition(x - (x % TILE_WIDTH), y - (y % TILE_HEIGHT));
        portalExit->setSize(TILE_WIDTH, TILE_HEIGHT);

        _portalExitLayer->addObject(portalExit);
    }

    // switches

    objectGroup = tiledMap->objectGroupNamed("switches");
    cocos2d::Array *switches = objectGroup->getObjects();

    CCARRAY_FOREACH(switches, ccObject)
    {
        dict = (cocos2d::Dictionary*) ccObject;

        id = ((cocos2d::String*) dict->objectForKey("name"))->intValue();
        x = ((cocos2d::String*) dict->objectForKey("x"))->intValue();
        y = ((cocos2d::String*) dict->objectForKey("y"))->intValue();
        width = ((cocos2d::String*) dict->objectForKey("width"))->intValue();
        height = ((cocos2d::String*) dict->objectForKey("height"))->intValue();
        
        bool oneTime = ((cocos2d::String*) dict->objectForKey("one_time"))->boolValue();
        bool bombSensitive = ((cocos2d::String*) dict->objectForKey("bomb_sensitive"))->boolValue();
        bool passingSensitive = ((cocos2d::String*) dict->objectForKey("passing_sensitive"))->boolValue();

        Switch *switchObject = (Switch *) ObjectCache::getInstance()->getObject(COT_SWITCH);
        switchObject->setId(id);
        switchObject->setPosition(x, y);
        switchObject->setSize(width, height);

        switchObject->setOneTime(oneTime);
        switchObject->setBombSensitive(bombSensitive);
        switchObject->setPassingSensitive(passingSensitive);

        _switchLayer->addObject(switchObject);
    }

    objectGroup = tiledMap->objectGroupNamed("switch_targets");
    cocos2d::Array *switchTargets = objectGroup->getObjects();

    CCARRAY_FOREACH(switchTargets, ccObject)
    {
        dict = (cocos2d::Dictionary*) ccObject;

        id = ((cocos2d::String*) dict->objectForKey("name"))->intValue();
        x = ((cocos2d::String*) dict->objectForKey("x"))->intValue();
        y = ((cocos2d::String*) dict->objectForKey("y"))->intValue();
        width = ((cocos2d::String*) dict->objectForKey("width"))->intValue();
        height = ((cocos2d::String*) dict->objectForKey("height"))->intValue();         

        GameObject *switchTarget = (GameObject *) ObjectCache::getInstance()->getObject(COT_GAME_OBJECT);
        switchTarget->setId(id);
        switchTarget->setPosition(x, y);
        switchTarget->setSize(width, height);

        _switchTargetLayer->addObject(switchTarget);
    }

    objectGroup = tiledMap->objectGroupNamed("spawnpoints");
    cocos2d::Array *spawnPoints = objectGroup->getObjects();

    CCARRAY_FOREACH(spawnPoints, ccObject)
    {
        dict = (cocos2d::Dictionary*) ccObject;

        x = ((cocos2d::String*) dict->objectForKey("x"))->intValue();
        y = ((cocos2d::String*) dict->objectForKey("y"))->intValue();
        //width = ((cocos2d::String*) dict->objectForKey("width"))->intValue();
        //height = ((cocos2d::String*) dict->objectForKey("height"))->intValue();

        _spawnPoint.first = x;
        _spawnPoint.second = y;
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

void GameState::setSpawnPoint(unsigned int id)
{
    _spriteLayer->getObject(id)->setPosition(_spawnPoint.first, _spawnPoint.second);
}

