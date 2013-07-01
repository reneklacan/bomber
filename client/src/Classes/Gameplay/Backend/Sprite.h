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

                virtual void configureFromGid(unsigned int gid);
                inline virtual bool isAI() { return false; };

            private:
                SYNTHESIZE(SpriteAttributes *, _attributes, Attributes);
        };
    }
}

#endif
