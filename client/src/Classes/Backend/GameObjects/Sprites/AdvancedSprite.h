#ifndef __BOMBER_ADVANCED_SPRITE
#define __BOMBER_ADVANCED_SPRITE

#include "../../AI/AdvancedAI.h"

namespace Bomber
{
    namespace Backend
    {
        class AdvancedSprite : public AdvancedAI
        {
            public:
                inline virtual Common::TCachableObjectType getObjectType()
                {
                    return Common::COT_ADVANCED_SPRITE;
                }

                AdvancedSprite();
                virtual void init();
        };
    }
}

#endif
