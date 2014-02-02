#ifndef __BOMBER_FRONTEND_ACHIEVEMENTBUTTON
#define __BOMBER_FRONTEND_ACHIEVEMENTBUTTON

#include "cocos2d.h"
#include "GameButton.h"
#include "../GUIConstants.h"

#include <string>

namespace Bomber
{
    namespace Frontend
    {
        class AchievementButton : public GameButton
        {
        public:
            AchievementButton(std::string title, std::string description, std::string image);

        private:
            unsigned int _width;
            unsigned int _height; 
        };
    }
}

#endif