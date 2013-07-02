#ifndef __BOMBER_BACKEND_RANDOM_AI
#define __BOMBER_BACKEND_RANDOM_AI

#include "../Sprite.h"
#include "../Primitives/Position.h"

namespace Bomber
{
    namespace Backend
    {
        enum TRandomAIState
        {
            STATE_NONE,
            STATE_MOVING
        };

        class RandomAI : public Sprite
        {
            public:
                RandomAI();
                void update(float dt);
                inline virtual bool isAI() { return true; };

            private:
                TRandomAIState _state;
                Position _goal;
        };
    }
}

#endif
