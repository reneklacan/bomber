#ifndef __BOMBER_BACKEND_BOMBER
#define __BOMBER_BACKEND_BOMBER

#include "../GameObject.h"

namespace Bomber
{
    namespace Backend
    {
        class BomberSprite : public Sprite
        {
            public:
                BomberSprite() : Sprite()
                {
                    _attributes->setSpeed(200);
                }
                virtual bool isBombPotent() { return true; };
        };
    }
}

#endif
