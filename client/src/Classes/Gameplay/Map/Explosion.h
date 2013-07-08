#ifndef __BOMBER_EXPLOSION
#define __BOMBER_EXPLOSION

#define EXPLOSION_CACHE_SIZE 16

#include "cocos2d.h"

using namespace cocos2d;

class ExplosionEmitterCache
{
    public:
        int _counter;
        int _cacheSize;
        ParticleSun *_emitters[EXPLOSION_CACHE_SIZE];
        static ExplosionEmitterCache *_instance;

        static ExplosionEmitterCache *getInstance();

        ExplosionEmitterCache();
        ParticleSun *getEmitter();
};


class Explosion : public Node
{
    public:
        Explosion(Point epicentrum, int powerLeft, int powerRight, int powerTop, int powerBottom);
};


#endif
