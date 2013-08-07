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
                inline virtual Common::TCachableObjectType getObjectType() { return Common::COT_AI_SPRITE; };

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
