#ifndef __BOMBER_BACKEND_BOMB
#define __BOMBER_BACKEND_BOMB

#include "ExplodableObject.h"

namespace Bomber
{
    namespace Backend
    {
        class BBomb : public ExplodableObject
        {
            public:
                BBomb();
                void configure(GameObject *owner);
                void update(float dt);
        };
    }
}

#endif

