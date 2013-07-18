#ifndef __BOMBER_BACKEND_BOMBER
#define __BOMBER_BACKEND_BOMBER

#include "../GameObject.h"

namespace Bomber
{
    namespace Backend
    {
        class Bomber : public Sprite
        {
            public:
                Bomber() : Sprite()
                {
                    _attributes->setSpeed(200);
                }
                virtual bool isBombPotent() { return true; };
        };
    }
}

#endif
