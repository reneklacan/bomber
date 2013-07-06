#ifndef __BOMBER_BACKEND_smart_FOLLOW_AI
#define __BOMBER_BACKEND_RANDOM_AI

#include "../Sprite.h"
#include "../Primitives/Position.h"

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
                void update(float dt);
                inline virtual bool isAI() { return true; };

            protected:
                bool _smart; // if AI is able to find path if obstacles are in direct path
                float _aggroDistance;

            private:
                TFollowAIState _state;
                Position _goal;
        };
    }
}

#endif
