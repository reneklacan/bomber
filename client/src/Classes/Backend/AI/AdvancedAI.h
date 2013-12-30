#ifndef __BOMBER_BACKEND_BEHAVIOUR
#define __BOMBER_BACKEND_BEHAVIOUR

#include <vector>

#include "Actions.h"
#include "../GameObjects/Sprites/Sprite.h"
#include "../../Common/Primitives/Position.h"

namespace Bomber
{
    namespace Backend
    {
        class AdvancedAI : public Sprite
        {
            public:
                AdvancedAI();

                void update(float dt);
                void nextAction();

                bool continueMove();
                void goToRandomDirection();
                void tryToChasePlayer();

                inline virtual bool isAI() { return true; };
                inline bool isMoving() { return _moving; };
                virtual Actions *behaviour() = 0;

            protected:
                std::vector<Action *> _actions;
                Common::Position _goal;
                float _step;
                bool _moving;
                SYNTHESIZE(bool, _smart, Smart); // if AI is able to find path if obstacles are in direct path
                SYNTHESIZE(float, _aggroDistance, AggroDistance);

                void setActions(Actions *);

            private:
                int _currentActionIndex = 0;
        };
    }
}

#endif
