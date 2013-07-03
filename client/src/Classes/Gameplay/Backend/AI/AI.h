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
                bool isCoordsCrossable(Coordinates coords);
                Coordinates getRandomCoordsAround(Coordinates coords);
                std::deque<Coordinates> findPath(Coordinates from, Coordinates to);
                std::deque<Coordinates> findPathToNearestPlayer(Coordinates from);

            private:
                AI();

                static AI *_instance;

                SYNTHESIZE_READONLY(GameState *, _state, State);
                SYNTHESIZE_READONLY(GameStateUpdater *, _gameStateUpdater, GameStateUpdater);
        };
    }
}

#endif
