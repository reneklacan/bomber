#ifndef __BOMBER_BACKEND_BOMB
#define __BOMBER_BACKEND_BOMB

#include "ExplodableObject.h"

namespace Bomber
{
    namespace Backend
    {
        class Bomb : public ExplodableObject
        {
            public:
                Bomb();
                void configure(GameObject *owner);
                void update(float dt);
                bool isDetonated() { return _detonated; };
        };
    }
}

#endif

