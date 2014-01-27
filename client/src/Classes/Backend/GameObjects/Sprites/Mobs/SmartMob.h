#ifndef __BOMBER_BACKEND_AI_SPRITE
#define __BOMBER_BACKEND_AI_SPRITE

#include "../AdvancedSprite.h"

namespace Bomber
{
    namespace Backend
    {
        class SmartMob : public AdvancedSprite
        {
            public:
                inline virtual Common::TCachableObjectType getObjectType()
                {
                    return Common::COT_SMART_MOB; 
                }

                SmartMob() : AdvancedSprite()
                {
                    //_attributes->setBombCapacity(2);
                    //_attributes->setGhostMode(true);
                    this->init();
                }

                virtual void init()
                {
                    _smart = true;
                    _aggroDistance = -1;
                    _attributes->setSpeed(50);

                    this->setActions(
                        new Actions(
                            new HuntNearestPlayer(),
                            new Again()
                        )
                    );
                }
        };
    }
}

#endif
