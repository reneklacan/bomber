#ifndef __BOMBER_BACKEND_ACHIEVEMENT_CONTAINER
#define __BOMBER_BACKEND_ACHIEVEMENT_CONTAINER

#include <list>
#include <deque>
#include "Statistics.h"
#include "Achievements.h"
#include "GameAchievements.h"

namespace Bomber
{
    namespace Backend
    {
        class AchievementContainer
        {
            public:
                static AchievementContainer *getInstance();
                void checkAll(Statistics *);
                std::list<Achievement *> getNewUnlocked();
                bool isNewQueueEmpty() { return !_newUnlocked.size(); };

            private:
                static AchievementContainer *_instance;
                AchievementContainer();
                std::list<AchievementObject *> _allAchievements;
                std::deque<Achievement *> _newUnlocked;
        };
    }
}

#endif
