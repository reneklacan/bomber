#ifndef __BOMBER_BACKEND_GAME_STATE_UPDATER
#define __BOMBER_BACKEND_GAME_STATE_UPDATER

#include "GameState.h"
#include "Primitives/Position.h"
#include "BBomb.h"
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

                void resetState();

                void updateSpriteGrid();
                void setState(GameState *state) { _state = state; };
                GameState *getState() { return _state; };
                unsigned int getUniqueId() { return _uniqueId++; };

                void moveSprite(Sprite *sprite, Position position);
                void teleportSprite(Sprite *sprite, Position position);
                
                void spawnSprite(unsigned int spriteGid, Coordinates coords);
                bool spawnBomb(Sprite* owner);
                void spawnExplosion(ExplodableObject *explObji, int topArmLength, int bottomArmLength, int leftArmLength, int rightArmLength);
                void spawnObstacle(unsigned int obstacleGid, Coordinates coords, unsigned int spawnerId);
                void spawnEffect(unsigned int effectGid, Coordinates coords);

                void updateSpriteAttributes(Sprite *sprite, Effect *effect);
                void updateAchievements();
                
                void switchLeverOn(GameObject *lever);
                void switchLeverOff(GameObject *lever);
                
                void damageSprite(Sprite *sprite, unsigned int causerId, int damage);
                void damageObstacle(Obstacle *obstacle, unsigned int causerId);

                void destroyObstacle(Obstacle *obstacle, unsigned int destroyerId);
                void destroySprite(Sprite *sprite);
                void destroyBomb(BBomb *bomb);
                void destroyEffect(Effect *effect);

                void logSpriteMove(Sprite *sprite);
                void logSpriteTeleport(Sprite *sprite, Position &to);
                void logSpriteDamage(Sprite *sprite, int damage);
                void logSpriteDestroy(Sprite *sprite);
                void logSpriteSpawn(unsigned int spriteGid, Sprite *sprite);
                void logBombSpawn(BBomb *bomb);
                void logObstacleSpawn(unsigned int obstacleGid, Obstacle *obstacle, unsigned int spawnerId);
                void logEffectSpawn(unsigned int effectGid, Effect *effect);
                void logBombDestroy(BBomb *bomb);
                void logExplosionSpawn(ExplodableObject *explObj, int topArmLength, int bottomArmLength, int leftArmLength, int rightArmLength);
                void logObstacleDestroy(Obstacle *obstacle);
                void logSpriteAttributesUpdate(Sprite *sprite, Effect *effect);
                void logLeverSwitchOn(GameObject *lever);
                void logLeverSwitchOff(GameObject *lever);
                void logEffectDestroy(Effect *effect);
                void logAchievementUnlocked(Achievement *achievement);

            private:
                GameState *_state;
                unsigned int _uniqueId;
        };
    }
}

#endif
