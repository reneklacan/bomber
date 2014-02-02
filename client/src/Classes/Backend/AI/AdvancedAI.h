#ifndef __BOMBER_BACKEND_ADVANCED_AI
#define __BOMBER_BACKEND_ADVANCED_AI

#include <deque>

#include "Actions.h"
#include "../../Common/Primitives/Position.h"
#include "ScriptedSprite.h"
#include "AI.h"

namespace Bomber
{
    namespace Backend
    {
        class AdvancedAI : public ScriptedSprite
        {
            public:
                AdvancedAI();
                AdvancedAI(Actions *actions);

                virtual void init();
                virtual void update(float dt);
                void nextAction();
                void runAction(Action *action);

                virtual bool continueMove();
                virtual bool continueMoveTo(Common::Coordinates coords);
                virtual void goRandom();
                virtual bool tryToChasePlayer();
                virtual void tryToChasePlayerOrGoRandom();

                inline virtual bool isAI() { return true; };
                inline virtual bool isAdvanced() { return true; };
                inline bool isMoving() { return _moving; };
                inline bool isInControl() { return _inControl; };

            protected:
                std::deque<Action *> _actions;
                std::deque<Action *> _defaultActions;
                Common::Position _goal;
                float _step;
                bool _moving;
                SYNTHESIZE(bool, _smart, Smart); // if AI is able to find path if obstacles are in direct path
                SYNTHESIZE(float, _aggroDistance, AggroDistance);

                void setActions(Actions *actions);

            private:
                //int _currentActionIndex;
                bool _inControl;
        };
    }
}

#endif
