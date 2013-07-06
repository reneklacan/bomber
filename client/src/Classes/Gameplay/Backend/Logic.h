#ifndef __BOMBER_LOGICv2
#define __BOMBER_LOGICv2

#include "GameState.h"
#include "BBomb.h"
#include "GameStateUpdater.h"

namespace Bomber
{
    namespace Backend
    {
        class Logic
        {
            public:
                static Logic* getInstance();

                void update(float dt);
                void setState(GameState *state) { _state = state; };

                void moveSprite(Position position);
                void moveSprite(unsigned int id, Position position);
                void moveSprite(GameObject *sprite, Position position);

                bool spawnBomb();
                bool spawnBomb(unsigned int);
                bool spawnBomb(Sprite *owner);

                void spawnExplosion(ExplodableObject *explObj);

                void logSpriteMove(GameObject *sprite, Position &from, Position &to);
                void logBombSpawn(BBomb *bomb);
                void logExplosionSpawn(ExplodableObject *explObj);
                
                void setControlledSprite(unsigned int id);
                void setGameStateUpdater(GameStateUpdater *updater);

            private:
                Logic();

                static Logic *_instance;
                GameState *_state;
                GameStateUpdater *_gameStateUpdater;
                Sprite *_controlledSprite;
        };
    }
}

#endif
