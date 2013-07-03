#ifndef __BOMBER_BOMB
#define __BOMBER_BOMB

#include "cocos2d.h"
#include "../Sprites/GameSprite.h"

using namespace cocos2d;

class Bomb : public GameSprite
{
    public:
        CC_SYNTHESIZE(GameSprite *, _owner, Owner);
        CC_SYNTHESIZE(Map *, _map, Map);
        CC_SYNTHESIZE(Point, _tilemapPosition, TilemapPosition);

        Bomb() : _detonated(false) {}

        static Bomb *create(Map *map, GameSprite *owner);
        bool isDetonated() { return _detonated; };
        void setDetonated() { _detonated = true; };

    private:
        bool _detonated;
};

class BombCache
{
    public:
        int _counter;
        int _cacheSize;
        Bomb *_bombs[4];
        static BombCache *_instance;

        static BombCache *getInstance();

        BombCache();
        Bomb *getBomb();
};


#endif

