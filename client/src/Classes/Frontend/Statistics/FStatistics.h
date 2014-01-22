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

            void countFinalScore();
            int getFinalScore();
            unsigned int getStars();

            SYNTHESIZE_STATS(unsigned int, _teleportations, Teleportation);
            SYNTHESIZE_STATS(unsigned int, _bombSpawns, BombSpawn);
            SYNTHESIZE_STATS(unsigned int, _achievementUnlocks, AchievementUnlock);
            SYNTHESIZE_STATS(unsigned int, _takenBuffs, TakenBuff);
            SYNTHESIZE_STATS(unsigned int, _usedLever, UsedLever);
            SYNTHESIZE_STATS(unsigned int, _killedMonster, KilledMonster);

        private:
            time_t _start;
            time_t _end;
            int _timer;
            time_t _pause;
            int _score;

        };
	}

}

#endif