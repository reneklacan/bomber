#ifndef __ACTION_DISPATCHER
#define __ACTION_DISPATCHER

#include "ActionDelegates.h"

class ActionDispatcher
{
    public:
        CC_SYNTHESIZE(PauseGameDelegate *, _pauseGameDelegate, PauseGameDelegate);
        CC_SYNTHESIZE(GameActionDelegate *, _gameActionDelefate, GameActionDelegate);
};

#endif
