#ifndef __BOMBER_BACKEND_GAME_STATE_UPDATER
#define __BOMBER_BACKEND_GAME_STATE_UPDATER

#include "../../Common/GameState/GameState.h"
#include "../../Common/Primitives/Position.h"
#include "../GameObjects/BBomb.h"
#include "../GameObjects/Obstacle.h"
#include "../GameObjects/Sprites/Sprite.h"
#include "../GameObjects/Effect.h"
#include "../Statistics/AchievementContainer.h"

namespace Bomber
{
    namespace Backend
    {
        class GameStateUpdater
        {
            public:
                GameStateUpdater();

                void resetState();
                void resetLevel();

                void updateSpriteGrid();
                void setState(Common::GameState *state) { _state = state; };
                Common::GameState *getState() { return _state; };
                unsigned int getUniqueId() { return _uniqueId++; };

                void moveSprite(Sprite *sprite, Common::Position position);
                void teleportSprite(Sprite *sprite, Common::Position position);

                void spawnSprite(unsigned int spriteGid, Common::Coordinates coords);
                void spawnBomb(Sprite* owner);
                void spawnExplosion(Bomb *bomb, int topArmLength, int bottomArmLength, int leftArmLength, int rightArmLength);
                void spawnObstacle(unsigned int obstacleGid, Common::Coordinates coords, unsigned int spawnerId);
                void spawnEffect(unsigned int effectGid, Common::Coordinates coords);

                void update();
                void updateSpriteAttributes(Sprite *sprite, Effect *effect);

                void pushBlock(Common::Coordinates from, Common::Coordinates to);
                void switchLeverOn(GameObject *lever, unsigned int causerId);
                void switchLeverOff(GameObject *lever, unsigned int causerId);

                void damageSprite(Sprite *sprite, unsigned int causerId, int damage);
                void damageObstacle(Obstacle *obstacle, unsigned int causerId);

                void destroyObstacle(Obstacle *obstacle, unsigned int destroyerId);
                void destroySprite(Sprite *sprite);
                void destroyBomb(Bomb *bomb);
                void destroyEffect(Effect *effect);
                void destroyDoor(GameObject *door);
                void destroyDoorKey(GameObject *doorKey);

                void logSpriteMove(Sprite *sprite);
                void logSpriteTeleport(Sprite *sprite, Common::Position &to);
                void logSpriteDamage(Sprite *sprite, int damage);
                void logSpriteDestroy(Sprite *sprite);
                void logSpriteSpawn(Sprite *sprite);
                void logBombSpawn(Bomb *bomb);
                void logBombMove(Bomb *bomb);
                void logObstacleSpawn(unsigned int obstacleGid, Obstacle *obstacle, unsigned int spawnerId);
                void logEffectSpawn(Effect *effect);
                void logBombDestroy(Bomb *bomb);
                void logExplosionSpawn(Bomb *bomb, int topArmLength, int bottomArmLength, int leftArmLength, int rightArmLength);
                void logObstacleDestroy(Obstacle *obstacle);
                void logSpriteAttributesUpdate(Sprite *sprite, Effect *effect);
                void logBlockPush(Common::Coordinates from, Common::Coordinates to);
                void logLeverSwitchOn(GameObject *lever);
                void logLeverSwitchOff(GameObject *lever);
                void logEffectDestroy(Effect *effect);
                void logAchievementUnlocked(Achievement *achievement);
                void logDialogBubble(char *title, char *text);
                void logDialogBubble();
                void logLevelFinish();
                void logLevelReset();

            private:
                Common::GameState *_state;
                unsigned int _uniqueId;
        };
    }
}

#endif
