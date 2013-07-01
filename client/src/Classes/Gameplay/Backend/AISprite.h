#ifndef __BOMBER_BACKEND_AI_SPRITE
#define __BOMBER_BACKEND_AI_SPRITE

#include "Sprite.h"

namespace Bomber
{
    namespace Backend
    {
        enum TAISpriteState
        {
            STATE_NONE,
            STATE_MOVING,
        };

        class AISprite : public Sprite
        {
            public:
                AISprite();

                virtual void update(float dt);
                //virtual void configureFromGid(unsigned int gid);
                inline virtual bool isAI() { return true; };

            private:
                SYNTHESIZE(SpriteAttributes *, _attributes, Attributes);
                TAISpriteState _state;
                Position _goal;
        };
    }
}

#endif
