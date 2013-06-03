#ifndef __BOMBER_BOMB
#define __BOMBER_BOMB

#include "cocos2d.h"
#include "../Sprites/GameSprite.h"

using namespace cocos2d;

class Bomb : public GameSprite
{
    public:
        CC_SYNTHESIZE(int, _power, Power);
        CC_SYNTHESIZE(float, _timeout, Timeout);
        CC_SYNTHESIZE(GameSprite *, _owner, Owner);
        CC_SYNTHESIZE(Map *, _map, Map);

        Bomb();

        static Bomb *create(Map *map, GameSprite *owner);
        //Bomb(CCPoint epicentrum, int power, float timeout);
        void update(float dt);
        void explode();

        bool isDetonated() { return _detonated; };

    private:
        float _expired;
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

