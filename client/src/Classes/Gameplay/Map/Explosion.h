#ifndef __BOMBER_EXPLOSION
#define __BOMBER_EXPLOSION

#include "cocos2d.h"

using namespace cocos2d;

class Explosion : public CCNode
{
    public:
        Explosion(CCPoint epicentrum, int power);
};

#endif
