#ifndef __BOMBER_GAME_STATE
#define __BOMBER_GAME_STATE

#include "GameStateLayer.h"
#include "GameStateChange.h"

namespace Bomber
{
    namespace Backend
    {
        class GameState
        {
            public:
                GameState();
                ~GameState();

                void addChange(GameStateChange *change);

                GameStateLayer *getBombLayer() { return _bombLayer; };

            private:
                std::vector<GameStateChange *> _changes;
                unsigned int _lastChangeId;

                GameStateLayer *_spriteLayer;
                GameStateLayer *_obstacleLayer;
                GameStateLayer *_portalLayer;
                GameStateLayer *_portalExitLayer;
                GameStateLayer *_specialLayer;
                GameStateLayer *_bombLayer;
        };
    }
}

#endif
