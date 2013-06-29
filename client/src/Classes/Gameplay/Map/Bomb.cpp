#include "Map.h"
#include "Bomb.h"
#include "Explosion.h"
#include "../../Constants.h"

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
        Bomb *bomb = Bomb::create(NULL, NULL);
        _bombs[i] = bomb;
    }
}

Bomb *BombCache::getBomb()
{
    return Bomb::create(NULL, NULL);
    _counter += 1;
    return _bombs[_counter % _cacheSize];
}

Bomb* Bomb::create(Map* map, GameSprite *owner)
{
    Bomb* sprite = new Bomb();

    if (sprite && sprite->initWithFile("tiles/bomb.png"))
    {
        sprite->setScale(0.1f);
        sprite->setOwner(owner);
        sprite->setMap(map);
        map->addChild(sprite, 0);
        sprite->setVertexZ(owner->getVertexZ()-1);
        sprite->autorelease();
        return sprite;
    }

    CC_SAFE_DELETE(sprite);
    return NULL;
}

Bomb::Bomb()
:_expired(0)
,_detonated(false)
,_power(1)
,_penetration(1)
{
    //this->schedule(schedule_selector(Bomb::updateTimer));
}

void Bomb::updateTimer(float dt)
{
    _expired += dt;

    if (_expired >= _timeout)
    {
        this->unschedule(schedule_selector(Bomb::updateTimer));
        this->setVisible(false);
        this->explode();
        _detonated = true;
    }
}

void Bomb::explode()
{
    return;

    Explosion *explosion = new Explosion(this->getPosition(), 3);
    explosion->autorelease();
    explosion->setVertexZ(this->getVertexZ());
    _map->addChild(explosion, 0);
}
