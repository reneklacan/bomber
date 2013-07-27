#ifndef __BOMBER_BACKEND_MEDIATOR
#define __BOMBER_BACKEND_MEDIATOR

#include "Logic.h"
#include "GameState/GameStateUpdater.h"
#include "../Common/Primitives/Direction.h"

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
                void setState(Common::GameState *state);
                void setControlledSprite(unsigned int id);
                Sprite *getControlledSprite();
                void moveSprite(Common::Position position);
                void spawnBomb();
                Common::GameState *getState() { return _state; }

                void pushObstacle(Common::Coordinates coords, Common::TDirection direction);
                void kickBomb(Common::Coordinates coords, Common::TDirection direction);

            private:
                Mediator();

                static Mediator *_instance;
                Common::GameState *_state;
                GameStateUpdater *_gameStateUpdater;
        };
    }
}

#endif
