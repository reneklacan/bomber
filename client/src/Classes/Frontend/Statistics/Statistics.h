#ifndef __BOMBER_FRONTEND_STATISTICS_LAYER
#define __BOMBER_FRONTEND_STATISTICS_LAYER

#include <ctime>

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

        private:
            time_t _start;
            time_t _end;
            int _timer;
            time_t _pause;
        };
	}

}

#endif