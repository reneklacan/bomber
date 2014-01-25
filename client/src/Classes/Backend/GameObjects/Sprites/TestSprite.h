#ifndef __BOMBER_BACKEND_TEST_SPRITE
#define __BOMBER_BACKEND_TEST_SPRITE

#include "../../AI/AdvancedAI.h"

namespace Bomber
{
    namespace Backend
    {
        class TestSprite : public AdvancedAI
        {
            public:
                TestSprite() : AdvancedAI()
                {
                    this->init();
                }

                virtual void init()
                {
                    _aggroDistance = 100;
                    _smart = true;

                    this->setActions(
                        new Actions(
                            new Wait(3),
                            new GoUp(3),
                            new Wait(1),
                            new GoDown(2),
                            new Wait(1),
                            new WalkWithoutAttentionTo(7, 7),
                            new Wait(3),
                            new GoUp(2),
                            new Wait(1),
                            new GoDown(2),
                            new Wait(1),
                            //new WalkTo(3, 3),
                            new HuntNearestPlayer(),
                            new Again()
                        )
                    );
                }
        };
    }
}

#endif
