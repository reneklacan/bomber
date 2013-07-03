#ifndef __BOMBER_BACKEND_AI_SPRITE
#define __BOMBER_BACKEND_AI_SPRITE

//#include "AI/RandomAI.h"
#include "AI/CleverFollowAI.h"

namespace Bomber
{
    namespace Backend
    {
        //class AISprite : public RandomAI
        class AISprite : public CleverFollowAI
        {
            public:
                //AISprite() : RandomAI()
                AISprite() : CleverFollowAI()
                {
                    this->getAttributes().setPortability(true);
                }
        };
    }
}

#endif
