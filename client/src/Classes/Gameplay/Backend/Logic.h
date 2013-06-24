
#ifndef __BOMBER_LOGICv2
#define __BOMBER_LOGICv2

#include "GameState.h"

namespace Bomber
{
    namespace Backend
    {
        class Logic
        {
            public:
                Logic();
                void update(float dt);

            private:
                GameState *_state;
        };
    }
}

#endif
