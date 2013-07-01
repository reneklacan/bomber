#ifndef __BOMBER_BACKEND_ACHIEVEMENT_CONTAINER
#define __BOMBER_BACKEND_ACHIEVEMENT_CONTAINER

#include <list>
#include "Statistics.h"

namespace Bomber
{
    namespace Backend
    {
        class AchievementContainer
        {
            public:
                AchievementContainer();

                void getObstacleCategory();
                void getKillCategory();
        };
    }
}

#endif
