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
                inline virtual TCachableObjectType getObjectType() { return COT_AI_SPRITE; };

                AISprite() : FollowAI()
                {
                    //_attributes->setBombCapacity(2);
                    //_attributes->setGhostMode(true);
                    this->init();
                }

                virtual void init()
                {
                    FollowAI::init();

                    _smart = true;
                    _attributes->setSpeed(50);
                }
        };
    }
}

#endif
