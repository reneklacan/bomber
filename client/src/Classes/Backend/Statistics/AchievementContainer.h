#ifndef __BOMBER_BACKEND_ACHIEVEMENT_CONTAINER
#define __BOMBER_BACKEND_ACHIEVEMENT_CONTAINER

#include <set>
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

                void checkType(TAchievConditionType type, Statistics *statistics);
                void checkAll(Statistics *statistics);
                std::list<Achievement *> getNewUnlocked();
                bool isNewQueueEmpty() { return !_newUnlocked.size(); };

            private:
                static AchievementContainer *_instance;

                AchievementContainer();

                std::list<AchievementGroup *> _allAchievementGroups;
                std::map<TAchievConditionType, std::set<AchievementGroup *> > _achievementGroupMap;
                std::deque<Achievement *> _newUnlocked;
        };
    }
}

#endif
