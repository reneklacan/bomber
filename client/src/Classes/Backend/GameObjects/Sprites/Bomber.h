#ifndef __BOMBER_BACKEND_BOMBER
#define __BOMBER_BACKEND_BOMBER

#include "AdvancedSprite.h"

namespace Bomber
{
    namespace Backend
    {
        class BomberSprite : public AdvancedSprite
        {
            public:
                inline virtual Common::TCachableObjectType getObjectType()
                {
                    return Common::COT_BOMBER_SPRITE;
                }

                BomberSprite() : AdvancedSprite()
                {
                    this->init();
                }

                virtual void init()
                {
                    AdvancedSprite::init();

                    _attributes->setSpeed(200);
                }
                inline virtual bool isBombPotent() { return true; };
                inline virtual bool isAI() { return false; };
        };
    }
}

#endif
