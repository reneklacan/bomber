#ifndef __BOMBER_BACKEND_GAME_ACHIEVEMENTS
#define __BOMBER_BACKEND_GAME_ACHIEVEMENTS

#include "Achievements.h"

namespace Bomber
{
    namespace Backend
    {
        std::list<AchievementObject *> getGameAchievements();
    }
}

#endif
