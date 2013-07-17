#ifndef __BOMBER_BACKEND_MEDIATOR
#define __BOMBER_BACKEND_MEDIATOR

#include "Logic.h"
#include "State/GameStateUpdater.h"
#include "Primitives/Direction.h"

namespace Bomber
{
    namespace Backend
    {
        class Mediator
        {
            public:
                static Mediator *getInstance();

                void update(float dt);
                void resetState();
                void setState(GameState *state);
                void setControlledSprite(unsigned int id);
                void moveSprite(Position position);
                void spawnBomb();
                GameState *getState() { return _state; }

                void pushObstacle(Coordinates coords, TDirection direction);
                void kickBomb(Coordinates coords, TDirection direction);

            private:
                Mediator();

                static Mediator *_instance;
                GameState *_state;
                GameStateUpdater *_gameStateUpdater;
        };
    }
}

#endif
