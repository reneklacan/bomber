#ifndef __BOMBER_BACKEND_TEST_SPRITE
#define __BOMBER_BACKEND_TEST_SPRITE

#include "../AdvancedSprite.h"

namespace Bomber
{
    namespace Backend
    {
        class ScriptedMob : public AdvancedSprite
        {
            public:
                inline virtual Common::TCachableObjectType getObjectType()
                {
                    return Common::COT_SCRIPTED_MOB;
                }

                ScriptedMob() : AdvancedSprite()
                {
                    this->init();
                }

                virtual void init()
                {
                    AdvancedSprite::init();

                    _aggroDistance = 100;
                    _smart = true;

                    this->setActions(
                        new Actions(
                            new Wait(3),
                            new GoUp(3),
                            new Wait(1),
                            new GoDown(2),
                            new Wait(1),
                            new WalkWithoutAttentionTo(12, 7),
                            new WalkWithoutAttentionTo(8, 7),
                            new Wait(3),
                            //new GoUp(2),
                            //new Wait(1),
                            //new GoDown(2),
                            //new Wait(1),
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
