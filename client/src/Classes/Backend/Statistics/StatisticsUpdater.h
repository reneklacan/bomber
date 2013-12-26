#ifndef __BOMBER_BACKEND_STATISTICS_UPDATER
#define __BOMBER_BACKEND_STATISTICS_UPDATER

#include "Statistics.h"
#include "../GameObjects/Sprites/Sprite.h"
#include "../GameObjects/BBomb.h"
#include "../GameObjects/Effect.h"
#include "../GameObjects/Obstacle.h"

namespace Bomber
{
    namespace Backend
    {
        class StatisticsUpdater
        {
            public:
                static StatisticsUpdater *getInstance();

                void resetLevelStatistics();

                void updateMobsAlive(int mobsAlive);
                void updateKillStreaks(unsigned int mobKills);
                void bombSpawned(unsigned int ownerId, Bomb *bomb);
                void effectTaken(unsigned int ownerId, Effect *effect);
                void monsterKilled(unsigned int ownerId, Sprite *monster);
                void obstacleDestroyed(unsigned int ownerId, Obstacle *obstacke);
                void teleportUsed(unsigned int ownerId);
                void leverUsed(unsigned int ownerId);
                
                inline void enable() { _enabled = true; };
                inline void disable() { _enabled = false; };

            private:
                StatisticsUpdater();

                static StatisticsUpdater *_instance;

                bool _enabled;
                SYNTHESIZE(unsigned int, _relevantSpriteId, RelevantSpriteId);

                SYNTHESIZE_READONLY(Statistics *, _levelStatistics, LevelStatistics);
                SYNTHESIZE_READONLY(Statistics *, _gameStatistics, GameStatistics);
        };
    }
}

#endif
