#ifndef __BOMBER_BACKEND_BOMB
#define __BOMBER_BACKEND_BOMB

#include "ExplodableObject.h"
#include "Sprites/Sprite.h"

namespace Bomber
{
    namespace Backend
    {
        class Bomb : public ExplodableObject
        {
            public:
                Bomb();
                void configure(Sprite *owner);
                void update(float dt);
        };
    }
}

#endif

