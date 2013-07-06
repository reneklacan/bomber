#ifndef __BOMBER_BACKEND_AI_SPRITE
#define __BOMBER_BACKEND_AI_SPRITE

#include "AI/FollowAI.h"

namespace Bomber
{
    namespace Backend
    {
        class AISprite : public FollowAI
        {
            public:
                AISprite() : FollowAI()
                {
                    _smart = false;
                    //_attributes.setGhostMode(true);
                }
        };
    }
}

#endif
