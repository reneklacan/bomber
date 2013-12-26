#ifndef __BOMBER_FRONTEND_GAMEBUTTON_LAYER
#define __BOMBER_FRONTEND_GAMEBUTTON_LAYER

#include "cocos2d.h"
#include "../../Input/ControlLayer.h"
#include <string>

namespace Bomber
{
    namespace Frontend
    {
        class GameButton
        {
        public:
            GameButton() {};

            unsigned int getWidth();
            unsigned int getHeight();
            Node *getGameButton();
            void setButtonPosition(Point *position);
            Point *getButtonPosition();

        protected:
            unsigned int _id;
            unsigned int _width;
            unsigned int _height;
            std::string _image;
            Point *_position;
            SEL_MenuHandler _handler;
            Object* _target;
            Node *_button;
        };

    }

}

#endif