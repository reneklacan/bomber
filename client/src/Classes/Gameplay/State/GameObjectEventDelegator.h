#ifndef __BOMBER_GAME_OBJECT_EVENT_DELEGATE
#define __BOMBER_GAME_OBJECT_EVENT_DELEGATE

#include "GameObjectEventDelegate.h"

class GameObjectEventDelegator
{
    virtual void setEventDelegate(GameObjectEventDelegate* delegate)
    {
        _eventDelegate = delegate;
    }
};

#endif
