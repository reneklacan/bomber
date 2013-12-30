#ifndef __BOMBER_BACKEND_TEST_SPRITE
#define __BOMBER_BACKEND_TEST_SPRITE

#include "../../AI/AdvancedAI.h"

namespace Bomber
{
    namespace Backend
    {
        class TestSprite : public AdvancedAI
        {
            TestSprite() : AdvancedAI()
            {
                this->init();
            }

            virtual void init()
            {
                this->setActions(this->behaviour());
            }

            virtual Actions *behaviour()
            {
                return new Actions(
                    new WalkTo(7, 14),
                    new Wait(15),
                    new WalkWithoutAttentionTo(3, 3),
                    new HuntNearestPlayer(),
                    new Again()
                );
            }
        };
    }
}

#endif
