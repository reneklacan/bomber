#ifndef __BOMBER_BACKEND_AI
#define __BOMBER_BACKEND_AI

#include "../../Common/GameState/GameState.h"
#include "../GameState/GameStateUpdater.h"

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

                void init(Common::GameState *state);
                void init(GameStateUpdater *gameStateUpdater);
                bool isCoordsCrossable(Common::Coordinates coords);
                bool isCoordsCrossable(Common::Coordinates coords, bool ghostMode);
                Common::Coordinates getRandomCoordsAround(Common::Coordinates coords);
                Common::Coordinates getRandomCoordsAround(Common::Coordinates coords, bool ghostMode);
                std::deque<Common::Coordinates> findDirectPath(Common::Coordinates from, Common::Coordinates to);
                std::deque<Common::Coordinates> findDirectPath(Common::Coordinates from, Common::Coordinates to, bool ghostMode);
                std::deque<Common::Coordinates> findPath(Common::Coordinates from, Common::Coordinates to);
                std::deque<Common::Coordinates> findPath(Common::Coordinates from, Common::Coordinates to, bool ghostMode);
                std::deque<Common::Coordinates> findPathToNearestPlayer(Common::Coordinates from, float range);
                std::deque<Common::Coordinates> findPathToNearestPlayer(Common::Coordinates from, float range, bool smart);
                std::deque<Common::Coordinates> findPathToNearestPlayer(Common::Coordinates from, float range, bool smart, bool ghostMode);

            private:
                AI();

                static AI *_instance;

                SYNTHESIZE_READONLY(Common::GameState *, _state, State);
                SYNTHESIZE_READONLY(GameStateUpdater *, _gameStateUpdater, GameStateUpdater);
        };
    }
}

#endif
