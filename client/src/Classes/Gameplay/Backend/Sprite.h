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
                static Sprite *getInstanceByGid(unsigned int gid);
                Sprite();
                ~Sprite();

                inline virtual bool isAI() { return false; };

            private:
                SYNTHESIZE(SpriteAttributes *, _attributes, Attributes);
        };
    }
}

#endif
