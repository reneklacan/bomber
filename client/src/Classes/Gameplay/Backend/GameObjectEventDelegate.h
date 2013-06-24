#ifndef __BOMBER_GAME_OBJECT_EVENT_DELEGATE
#define __BOMBER_GAME_OBJECT_EVENT_DELEGATE

#include "GameStateChange.h"

namespace Bomber
{
    namespace Backend
    {
        class GameObjectEventDelegate
        {
            public:
                virtual void update(GameStateChange *change) = 0;
        };
    }
}

#endif
