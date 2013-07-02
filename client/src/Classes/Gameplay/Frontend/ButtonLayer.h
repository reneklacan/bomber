#ifndef __BOMBER_FRONTEND_BUTTON_LAYER
#define __BOMBER_FRONTEND_BUTTON_LAYER

#include "cocos2d.h"

#include <vector>

#include "GameButton.h"

namespace Bomber
{
    namespace Frontend
    {
        class ButtonLayer
        {
        public:
            static ButtonLayer *getInstance();

            void addToSkills(GameButton *skill);
            void addToBuffs(GameButton *buff);
            void addToAchievementss(GameButton *achievement);
            void addToControls(GameButton *control);

        private:
            ButtonLayer() {};

            std::vector<GameButton *> _skills;
            std::vector<GameButton *> _buffs;
            std::vector<GameButton *> _achievements;
            std::vector<GameButton *> _controls;
        };
    }
}

#endif