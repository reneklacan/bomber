#ifndef __BOMBER_BACKEND_SPRITE
#define __BOMBER_BACKEND_SPRITE

#include "GameObject.h"
#include "SpriteAttributes.h"
#include "Macros.h"

namespace Bomber
{
    namespace Backend
    {
        class Sprite : public GameObject
        {
            public:
                Sprite();

            private:
                SYNTHESIZE(SpriteAttributes *, _attributes, Attributes);
        };
    }
}

#endif
