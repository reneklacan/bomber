#ifndef __BOMBER_BACKEND_AI
#define __BOMBER_BACKEND_AI

#include "../GameState.h"
#include "../GameStateUpdater.h"

namespace Bomber
{
    namespace Backend
    {
        enum TAIType
        {
            AI_RANDOM,
        };

        class AI
        {
            public:
                static AI *getInstance();

                void init(GameState *state);
                void init(GameStateUpdater *gameStateUpdater);
                Coordinates getRandomCoordsAround(Coordinates coords);

            private:
                AI();

                static AI *_instance;

                SYNTHESIZE_READONLY(GameState *, _state, State);
                SYNTHESIZE_READONLY(GameStateUpdater *, _gameStateUpdater, GameStateUpdater);
        };
    }
}

#endif
