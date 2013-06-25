#ifndef __BOMBER_BACKEND_MEDIATOR
#define __BOMBER_BACKEND_MEDIATOR

#include "Logic.h"

namespace Bomber
{
    namespace Backend
    {
        class Mediator
        {
            public:
                static Mediator *getInstance();

                Mediator();

                void setState(GameState *state);
                void setControlledSprite(unsigned int id);
                void moveSprite(Position position);
                void spawnBomb();

            private:
                static Mediator *_instance;
                GameState *_state;
        };
    }
}

#endif
