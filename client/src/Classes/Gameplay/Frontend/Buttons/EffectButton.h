#ifndef __BOMBER_FRONTEND_EFFECTBUTTON
#define __BOMBER_FRONTEND_EFFECTBUTTON

#include "cocos2d.h"
#include "GameButton.h"

namespace Bomber
{
    namespace Frontend
    {
        class EffectButton : public GameButton
        {
        public:
            EffectButton(Rect imageRect, Texture2D *texture);

        private:
        };

    }
}

#endif