#ifndef __BOMBER_CONTROLLER_BASE
#define __BOMBER_CONTROLLER_BASE

#include "cocos2d.h"

using namespace cocos2d;

class GameController
{
    public:
        CC_SYNTHESIZE(CCPoint, _velocity, Velocity);
        CC_SYNTHESIZE(bool, _enabled, Enabled);

        //virtual bool init() = 0;
        virtual bool isActionKeyOnePressed() { return _actionKeyOnePressed; };
        virtual bool isEnabled() { return _enabled; };
        virtual const char *getName() { return "GameController"; };

    protected:
        bool _actionKeyOnePressed;
};

#endif
