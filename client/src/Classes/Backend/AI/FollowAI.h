#ifndef __BOMBER_BACKEND_FOLLOW_AI
#define __BOMBER_BACKEND_FOLLOW_AI

#include "../GameObjects/Sprites/Sprite.h"
#include "../../Common/Primitives/Position.h"

namespace Bomber
{
    namespace Backend
    {
        enum TFollowAIState
        {
            STATE_NONE,
            STATE_MOVING
        };

        class FollowAI : public Sprite
        {

            public:
                FollowAI();
                virtual void init();
                void update(float dt);
                inline virtual bool isAI() { return true; };

            private:
                TFollowAIState _state;
                Common::Position _goal;
                SYNTHESIZE(bool, _smart, Smart); // if AI is able to find path if obstacles are in direct path
                SYNTHESIZE(float, _aggroDistance, AggroDistance);
        };
    }
}

#endif
