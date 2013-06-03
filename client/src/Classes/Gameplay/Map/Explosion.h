#ifndef __BOMBER_EXPLOSION
#define __BOMBER_EXPLOSION

#include "cocos2d.h"

using namespace cocos2d;

class ExplosionCache
{
    public:
        int _counter;
        int _cacheSize;
        CCParticleSun *_emitters[4];
        static ExplosionCache *_instance;

        static ExplosionCache *getInstance();

        ExplosionCache();
        CCParticleSun *getEmitter();
};


class Explosion : public CCNode
{
    public:
        Explosion(CCPoint epicentrum, int power);
};


#endif
