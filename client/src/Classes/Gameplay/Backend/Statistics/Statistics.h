#ifndef __BOMBER_BACKEND_STATISTICS
#define __BOMBER_BACKEND_STATISTICS

#include <map>

#include "Statistics.h"
#include "../Macros.h"
#include "../Sprite.h"
#include "../Bomb.h"
#include "../Effect.h"
#include "../Obstacle.h"

namespace Bomber
{
    namespace Backend
    {
        typedef std::map<const char *, unsigned int> TStatsDict;

        class Statistics
        {
            public:
                Statistics();

                void reset();

                void increaseBombSpawns();
                void increaseKills(const char *name);
                void increaseEffects(const char *name);
                void increaseObstacles(const char *name);

                void print();

            private:
                SYNTHESIZE(unsigned int, _bombSpawns, BombSpawns);
                SYNTHESIZE(unsigned int, _totalKills, TotalKills);
                SYNTHESIZE(TStatsDict, _kills, Kills);
                SYNTHESIZE(unsigned int, _totalEffects, TotalEffects);
                SYNTHESIZE(TStatsDict, _effects, Effects);
                SYNTHESIZE(unsigned int, _totalObstacles, TotalObstacles);
                SYNTHESIZE(TStatsDict, _obstacles, Obstacles);
        };
    }
}

#endif
