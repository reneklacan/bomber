#ifndef __BOMBER_FRONTEND_GAMEBUTTON_LAYER
#define __BOMBER_FRONTEND_GAMEBUTTON_LAYER

#include "cocos2d.h"
#include "../../Input/ControlLayer.h"
#include <vector>
#include <map>
#include <iostream>

namespace Bomber
{
    namespace Frontend
    {
        class GameButton : public CCMenu
        {
        public:
            ~GameButton() {}

            GameButton *createButton(CCObject* target, SEL_MenuHandler handler);

        private:
            void addButton(GameButton *button, unsigned int width, unsigned int height);
            std::map<GameButton *, CCPoint> _buttons;
            std::vector<GameButton *> _buttonsOrder;
        };

    }

}

#endif