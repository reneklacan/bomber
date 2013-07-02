#ifndef __BOMBER_FRONTEND_CONTROLBUTTON
#define __BOMBER_FRONTEND_CONTROLBUTTON

#include "cocos2d.h"
#include "GameButton.h"

namespace Bomber
{
    namespace Frontend
    {
        class ControlButton : public GameButton
        {
        public:
            ControlButton(unsigned int id, std::string image, CCObject* target, SEL_MenuHandler hadler);
        };
    }
}

#endif