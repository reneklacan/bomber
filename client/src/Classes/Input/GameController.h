#ifndef __BOMBER_CONTROLLER_BASE
#define __BOMBER_CONTROLLER_BASE

#include "cocos2d.h"

#include "ActionDispatcher.h"

using namespace cocos2d;

class GameController : public Layer, public ActionDispatcher
{
    public:
        CC_SYNTHESIZE(Point, _player1Velocity, Player1Velocity);
        CC_SYNTHESIZE(Point, _player2Velocity, Player2Velocity);
        CC_SYNTHESIZE(bool, _enabled, Enabled);

        virtual bool isEnabled() { return _enabled; };
        virtual const char *getName() { return "GameController"; };
};

#endif
