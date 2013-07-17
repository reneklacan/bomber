#ifndef __BOMBER_BACKEND_AI_SPRITE
#define __BOMBER_BACKEND_AI_SPRITE

#include "../../AI/FollowAI.h"

namespace Bomber
{
    namespace Backend
    {
        class AISprite : public FollowAI
        {
            public:
                AISprite() : FollowAI()
                {
                    _smart = true;
                    _attributes->setSpeed(50);
                    //_attributes->setBombCapacity(2);
                    //_attributes->setGhostMode(true);
                }
        };
    }
}

#endif
