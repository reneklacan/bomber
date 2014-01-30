
#include "stdio.h"

#include "ObjectCache.h"

#include "../../Backend/GameObjects/Effect.h"
#include "../../Backend/GameObjects/BBomb.h"
#include "../../Backend/GameObjects/Portal.h"
#include "../../Backend/GameObjects/PortalExit.h"
#include "../../Backend/GameObjects/Obstacle.h"
#include "../../Backend/GameObjects/Switch.h"
#include "../../Backend/GameObjects/Sprites/AdvancedSprite.h"
#include "../../Backend/GameObjects/Sprites/Bomber.h"
#include "../../Backend/GameObjects/Sprites/Mobs/SmartMob.h"
#include "../../Backend/GameObjects/Sprites/Mobs/ScriptedMob.h"

using namespace Bomber::Common;
using namespace Bomber::Backend;

ObjectCache *ObjectCache::_instance = nullptr;

ObjectCache *ObjectCache::getInstance()
{
    if (_instance == nullptr)
    {
        _instance = new ObjectCache();
    }
    return _instance;
}

ObjectCache::ObjectCache()
{
    _enabled = true;
}

CachableObject* ObjectCache::getObject(TCachableObjectType type)
{
    CachableObject* object = nullptr;

    if (_enabled && _freeInstances[type].size() > 0)
    {
        object = _freeInstances[type].front();
        object->init();

        _freeInstances[type].pop_front();
        _occupiedInstances[type].insert(object);

        return object;
    }

    switch (type)
    {
        case COT_BOMB:
            object = new Bomb();
            break;
        case COT_GAME_OBJECT:
            object = new GameObject();
            break;
        case COT_PORTAL:
            object = new Portal();
            break;
        case COT_PORTAL_EXIT:
            object = new PortalExit();
            break;
        case COT_SWITCH:
            object = new Switch();
            break;

        // sprites

        case COT_ADVANCED_SPRITE:
            object = new AdvancedSprite();
            break;
        case COT_BOMBER_SPRITE:
            object = new BomberSprite();
            break;
        case COT_SMART_MOB:
            object = new SmartMob();
            break;
        case COT_SCRIPTED_MOB:
            object = new ScriptedMob();
            break;

        // blocks

        case COT_MAZE_BLOCK:
            object = new MazeBlock();
            break;
        case COT_LEVER_BLOCK:
            object = new LeverBlock();
            break;
        case COT_DESTROYABLE_BLOCK:
            object = new DestroyableBlock();
            break;
        case COT_PUSHABLE_BLOCK:
            object = new PushableBlock();
            break;

        // effects

        case COT_BOMB_POWER_INC:
            object = new EffectBombPowerInc();
            break;
        case COT_BOMB_CAPACITY_INC:
            object = new EffectBombCapacityInc();
            break;
        case COT_PORTABILITY_ON:
            object = new EffectPortabilityOn();
            break;
        case COT_PORTABILITY_OFF:
            object = new EffectPortabilityOff();
            break;
        case COT_HEALTH_INC:
            object = new EffectHealthInc();
            break;
        case COT_HEALTH_DEC:
            object = new EffectHealthDec();
            break;
        case COT_SPEED_INC:
            object = new EffectSpeedInc();
            break;
        case COT_SPEED_DEC:
            object = new EffectSpeedDec();
            break;
        case COT_LEVEL_KEY:
            object = new EffectLevelKey();
            break;
        case COT_FIRE_IMMUNITY:
            object = new EffectFireImmunity();
            break;
        case COT_WATER_IMMUNITY:
            object = new EffectWaterImmunity();
            break;
        case COT_CLEAR_IMMUNITIES:
            object = new EffectClearImmunities();
            break;
        case COT_FIRE_TRAP:
            object = new EffectFireTrap();
            break;
        case COT_WATER_TRAP:
            object = new EffectWaterTrap();
            break;
        case COT_SHIFT_UP:
            object = new EffectShiftUp();
            break;
    }

    if (object == nullptr)
    {
        printf("BackendCache error\n");
        return nullptr;
    }
                    
    _occupiedInstances[type].insert(object);

    //printf("occupied cache size for type %d is %u\n", type, _occupiedInstances[type].size());

    return object;
}

void ObjectCache::returnObject(CachableObject *object)
{
    TCachableObjectType type = object->getObjectType();
    _occupiedInstances[type].erase(object);
    _freeInstances[type].push_back(object);
    
    //printf("occupied cache size for type %d is %u\n", type, _occupiedInstances[type].size());
}

void ObjectCache::reset(TCachableObjectType type)
{
    for (auto object : _occupiedInstances[type])
    {
        _freeInstances[type].push_back(object);
    }
    _occupiedInstances[type].clear();
}

void ObjectCache::reset()
{
    for (auto pair : _occupiedInstances)
    {
        TCachableObjectType type = pair.first;
        this->reset(type);
    }
}

void ObjectCache::free(TCachableObjectType type)
{
    this->reset(type);

    for (auto object : _freeInstances[type])
    {
        delete object;
    }
    _freeInstances[type].clear();
}

void ObjectCache::free()
{
    for (auto pair : _freeInstances)
    {
        TCachableObjectType type = pair.first;
        this->free(type);
    }
}
