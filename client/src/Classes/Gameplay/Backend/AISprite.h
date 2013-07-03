#ifndef __BOMBER_BACKEND_AI_SPRITE
#define __BOMBER_BACKEND_AI_SPRITE

#include "AI/RandomAI.h"

namespace Bomber
{
    namespace Backend
    {
        class AISprite : public RandomAI
        {
            public:
                AISprite() : RandomAI()
                {
                    this->getAttributes().setPortability(true);
                }
        };
    }
}

#endif
