#ifndef __BOMBER_BACKEND_STATISTICS_UPDATER
#define __BOMBER_BACKEND_STATISTICS_UPDATER

#include "Statistics.h"
#include "../Sprite.h"
#include "../BBomb.h"
#include "../Effect.h"
#include "../Obstacle.h"

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
                void bombSpawned(unsigned int ownerId, BBomb *bomb);
                void effectTaken(unsigned int ownerId, Effect *effect);
                void monsterKilled(unsigned int ownerId, Sprite *monster);
                void obstacleDestroyed(unsigned int ownerId, Obstacle *obstacke);

            private:
                StatisticsUpdater();

                static StatisticsUpdater *_instance;

                SYNTHESIZE_READONLY(Statistics *, _levelStatistics, LevelStatistics);
                SYNTHESIZE_READONLY(Statistics *, _gameStatistics, GameStatistics);
        };
    }
}

#endif
