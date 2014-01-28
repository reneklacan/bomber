#ifndef __BOMBER_BACKEND_ADVANCED_AI
#define __BOMBER_BACKEND_ADVANCED_AI

#include <vector>

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

                virtual bool continueMove();
                virtual bool continueMoveTo(Common::Coordinates coords);
                virtual void goRandom();
                virtual bool tryToChasePlayer();
                virtual void tryToChasePlayerOrGoRandom();

                inline virtual bool isAI() { return true; };
                inline bool isMoving() { return _moving; };

            protected:
                std::vector<Action *> _actions;
                Common::Position _goal;
                float _step;
                bool _moving;
                SYNTHESIZE(bool, _smart, Smart); // if AI is able to find path if obstacles are in direct path
                SYNTHESIZE(float, _aggroDistance, AggroDistance);

                void setActions(Actions *);

            private:
                int _currentActionIndex;
        };
    }
}

#endif
