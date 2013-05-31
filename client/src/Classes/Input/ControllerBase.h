#ifndef __BOMBER_CONTROLLER_BASE
#define __BOMBER_CONTROLLER_BASE

#include "cocos2d.h"

using namespace cocos2d;

class ControllerBase
{
    public:
        CC_SYNTHESIZE(CCPoint, _velocity, Velocity);

        virtual bool init() = 0;

    private:
        bool _enabled;

};

#endif
