#ifndef __BOMBER_EXPLOSION
#define __BOMBER_EXPLOSION

#include "cocos2d.h"

using namespace cocos2d;

class ExplosionCache
{
    public:
        int _counter;
        int _cacheSize;
        ParticleSun *_emitters[4];
        static ExplosionCache *_instance;

        static ExplosionCache *getInstance();

        ExplosionCache();
        ParticleSun *getEmitter();
};


class Explosion : public Node
{
    public:
        Explosion(Point epicentrum, int powerLeft, int powerRight, int powerTop, int powerBottom);
};


#endif
