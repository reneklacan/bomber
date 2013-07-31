#ifndef __BOMBER_FRONTEND_BUTTON_LAYER
#define __BOMBER_FRONTEND_BUTTON_LAYER

#include "cocos2d.h"

#include <vector>

#include "Buttons/GameButton.h"
#include "Buttons/EffectButton.h"

namespace Bomber
{
    namespace Frontend
    {
        class ButtonLayer : public Layer
        {
        public:
            static ButtonLayer *getInstance();

            void addToSkills(GameButton *skill);
            void addToBuffs(GameButton *buff);
            void addToAchievements(GameButton *achievement);
            void addToControls(GameButton *control);
            void setMainLayer(Layer* main);
            void saveTime(float dt);
            bool isInBuffs(unsigned int id);
            void incrementBuff(unsigned int id);

            void reset();
            void resetAll();

        private:
            ButtonLayer();

            void addAchievement();
            void removeAchievement();

            Layer *_mainLayer;
            std::vector<GameButton *> _skills;
            std::vector<GameButton *> _buffs;
            std::vector<GameButton *> _achievements;
            std::vector<GameButton *> _controls;
            float _time;
            bool _saveTime;
        };
    }
}

#endif