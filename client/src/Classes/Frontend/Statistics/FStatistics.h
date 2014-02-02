#ifndef __BOMBER_FRONTEND_STATISTICS_LAYER
#define __BOMBER_FRONTEND_STATISTICS_LAYER

#include <ctime>
#include "../../Macros.h"

namespace Bomber
{

	namespace Frontend
	{
		class Statistics
        {
        public:
            void startLevelTimer();
            void endLevelTimer();
            void pauseLevelTimer();
            void resumeLevelTimer();
            int getLevelTimer();

            int getFinalScore();
            unsigned int getStars();

            SYNTHESIZE(unsigned int, _bombSpawns, BombSpawns);
            SYNTHESIZE(unsigned int, _killedMonsters, KilledMonsters);
            SYNTHESIZE(unsigned int, _takenBuffs, TakenBuffs);
            SYNTHESIZE(unsigned int, _destroyedObstacles, DestroyedObstacles);
            SYNTHESIZE(unsigned int, _teleportations, Teleportations);
            SYNTHESIZE(unsigned int, _usedLevers, UsedLevers);
            SYNTHESIZE_STATS(unsigned int, _achievementUnlocks, AchievementUnlock);
            SYNTHESIZE_STATS(unsigned int, _ranUnit, RanUnit);

        private:
            time_t _start;
            time_t _end;
            int _timer;
            time_t _pause;
            int _score;

            void countRanDistance();
            void countFinalScore();

        };
	}

}

#endif