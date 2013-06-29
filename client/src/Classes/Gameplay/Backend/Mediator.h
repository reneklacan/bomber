#ifndef __BOMBER_BACKEND_MEDIATOR
#define __BOMBER_BACKEND_MEDIATOR

#include "Logic.h"
#include "GameStateUpdater.h"

namespace Bomber
{
    namespace Backend
    {
        class Mediator
        {
            public:
                static Mediator *getInstance();

                void update(float dt);
                void setState(GameState *state);
                void setControlledSprite(unsigned int id);
                void moveSprite(Position position);
                void spawnBomb();

            private:
                Mediator();

                static Mediator *_instance;
                GameState *_state;
                GameStateUpdater *_gameStateUpdater;
        };
    }
}

#endif
