
#include "BackendCache.h"

using namespace Bomber::Backend;

BackendCache *BackendCache::_instance = nullptr;

BackendCache *BackendCache::getInstance()
{
    if (_instance == nullptr)
    {
        _instance = new BackendCache();
    }
    return _instance;
}

BackendCache::BackendCache()
{
    _enabled = true;
}

CachableObject* BackendCache::getObject(TCachableObjectType type)
{
    CachableObject* object = nullptr;

    if (_enabled && _freeInstances[type].size() > 0)
    {
        object = _freeInstances[type].front();
        object->init();

        _freeInstances[type].pop_front();
        _occupiedInstances[type].insert(object);

        printf("occupied cache size for type %d is %u\n", type, _occupiedInstances[type].size());

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
    }

    if (object == nullptr)
    {
        printf("BackendCache error\n");
        return nullptr;
    }
                    
    _occupiedInstances[type].insert(object);

    printf("occupied cache size for type %d is %u\n", type, _occupiedInstances[type].size());

    return object;
}

void BackendCache::returnObject(CachableObject *object)
{
    TCachableObjectType type = object->getObjectType();
    _occupiedInstances[type].erase(object);
    _freeInstances[type].push_back(object);
    
    printf("occupied cache size for type %d is %u\n", type, _occupiedInstances[type].size());
}

void BackendCache::reset(TCachableObjectType type)
{
    for (auto object : _occupiedInstances[type])
    {
        _freeInstances[type].push_back(object);
    }
    _occupiedInstances.clear();
}

void BackendCache::reset()
{
    for (auto pair : _occupiedInstances)
    {
        TCachableObjectType type = pair.first;
        this->reset(type);
    }
}