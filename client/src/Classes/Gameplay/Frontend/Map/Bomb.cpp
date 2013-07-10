#include "Map.h"
#include "Bomb.h"
#include "Explosion.h"
#include "../../../Constants.h"

using namespace Bomber::Frontend;

BombCache *BombCache::_instance = NULL;

BombCache *BombCache::getInstance()
{
    if (_instance == NULL)
        _instance = new BombCache();
    return _instance;
}

BombCache::BombCache()
{
    _cacheSize = 12;
    _counter = -1;

    for (int i = 0; i < _cacheSize; i++)
    {
        Bomb *bomb = Bomb::create(NULL, NULL, NULL);
        _bombs[i] = bomb;
    }
}

Bomb *BombCache::getBomb()
{
    return Bomb::create(NULL, NULL, NULL);
    _counter += 1;
    return _bombs[_counter % _cacheSize];
}

Bomb* Bomb::create(Map* map, SpriteBatchNode* batchNode, GameSprite *owner)
{
    Bomb* sprite = new Bomb();

    if (sprite && sprite->initWithTexture(batchNode->getTexture(), CCRectMake(6*120+15,10*60-20,80,110)) )
    {
        sprite->setOwner(owner);
        sprite->setMap(map);
        batchNode->addChild(sprite, 0);
        sprite->autorelease();
        return sprite;
    }

    CC_SAFE_DELETE(sprite);
    return NULL;
}

