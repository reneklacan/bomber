#ifndef __BOMBER_BACKEND_BOMB
#define __BOMBER_BACKEND_BOMB

#include "ExplodableObject.h"
#include "Sprite.h"

namespace Bomber
{
    namespace Backend
    {
        class BBomb : public ExplodableObject
        {
            public:
                BBomb();
                void configure(Sprite *owner);
                void update(float dt);
        };
    }
}

#endif

