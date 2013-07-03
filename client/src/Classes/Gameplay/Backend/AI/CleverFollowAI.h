#ifndef __BOMBER_BACKEND_CLEVER_FOLLOW_AI
#define __BOMBER_BACKEND_RANDOM_AI

#include "../Sprite.h"
#include "../Primitives/Position.h"

namespace Bomber
{
    namespace Backend
    {
        enum TCleverFollowAIState
        {
            STATE_NONE,
            STATE_MOVING
        };

        class CleverFollowAI : public Sprite
        {
            public:
                CleverFollowAI();
                void update(float dt);
                inline virtual bool isAI() { return true; };

            private:
                TCleverFollowAIState _state;
                Position _goal;
        };
    }
}

#endif
