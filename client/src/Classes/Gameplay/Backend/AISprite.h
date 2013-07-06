#ifndef __BOMBER_BACKEND_AI_SPRITE
#define __BOMBER_BACKEND_AI_SPRITE

//#include "AI/RandomAI.h"
#include "AI/FollowAI.h"

namespace Bomber
{
    namespace Backend
    {
        //class AISprite : public RandomAI
        class AISprite : public FollowAI
        {
            public:
                //AISprite() : RandomAI()
                AISprite() : FollowAI()
                {
                    this->getAttributes().setPortability(true);
                }
        };
    }
}

#endif
