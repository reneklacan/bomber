#ifndef __BOMBER_BACKEND_GAME_STATE_UPDATER
#define __BOMBER_BACKEND_GAME_STATE_UPDATER

#include "GameState.h"
#include "Position.h"
#include "Bomb.h"
#include "Obstacle.h"

namespace Bomber
{
    namespace Backend
    {
        class GameStateUpdater
        {
            public:
                GameStateUpdater();

                void updateGrid();
                void setState(GameState *state) { _state = state; };
                GameState *getState() { return _state; };
                unsigned int getUniqueId() { return _uniqueId++; };

                bool moveSprite(GameObject *sprite, Position position);
                bool teleportSprite(GameObject *sprite, Position position);
                bool spawnBomb(GameObject *owner);
                void spawnExplosion(ExplodableObject *explObj);
                void destroyBomb(Bomb *bomb);
                void makeBombImpact(int *penetration, unsigned int x, unsigned int y);

                void logSpriteMove(GameObject *sprite, Position &from, Position &to);
                void logSpriteTeleport(GameObject *sprite, Position &to);
                void logBombSpawn(Bomb *bomb);
                void logBombDestroy(Bomb *bomb);
                void logExplosionSpawn(ExplodableObject *explObj);
                void logObstacleDestroy(Obstacle *obstacle);

            private:
                GameState *_state;
                unsigned int _uniqueId;
        };
    }
}

#endif
