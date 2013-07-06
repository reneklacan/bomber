#ifndef __BOMBER_BACKEND_GAME_STATE_UPDATER
#define __BOMBER_BACKEND_GAME_STATE_UPDATER

#include "GameState.h"
#include "Primitives/Position.h"
#include "Bomb.h"
#include "Obstacle.h"
#include "Sprite.h"
#include "Effect.h"
#include "Statistics/AchievementContainer.h"

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

                void moveSprite(GameObject *sprite, Position position);
                void teleportSprite(GameObject *sprite, Position position);
                bool spawnBomb(Sprite* owner);
                void spawnExplosion(ExplodableObject *explObji, int topArmLength, int bottomArmLength, int leftArmLength, int rightArmLength);
                void destroyBomb(Bomb *bomb);
                bool makeBombImpact(unsigned int owner, int *penetration, unsigned int x, unsigned int y);
                void updateSpriteAttributes(Sprite *sprite, Effect *effect);
                void destroyEffect(Effect *effect);
                void updateAchievements();

                void logSpriteMove(GameObject *sprite);
                void logSpriteTeleport(GameObject *sprite, Position &to);
                void logBombSpawn(Bomb *bomb);
                void logBombDestroy(Bomb *bomb);
                void logExplosionSpawn(ExplodableObject *explObj, int topArmLength, int bottomArmLength, int leftArmLength, int rightArmLength);
                void logObstacleDestroy(Obstacle *obstacle);
                void logSpriteAttributesUpdate(Sprite *sprite, Effect *effect);
                void logEffectDestroy(Effect *effect);
                void logAchievementUnlocked(Achievement *achievement);

            private:
                GameState *_state;
                unsigned int _uniqueId;
        };
    }
}

#endif
