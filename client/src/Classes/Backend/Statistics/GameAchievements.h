#ifndef __BOMBER_BACKEND_GAME_ACHIEVEMENTS
#define __BOMBER_BACKEND_GAME_ACHIEVEMENTS

#include "Achievements.h"
#include <stdarg.h>

namespace Bomber
{
    namespace Backend
    {
        class GameAchievements
        {
            public:
                GameAchievements(AchievementGroup *group, ...)
                {
                    _achievementGroups.push_back(group);

                    va_list list;
                    va_start(list, group);

                    while (true)
                    {
                        AchievementGroup *g = va_arg(list, AchievementGroup *);

                        if (g == nullptr)
                            break;

                        _achievementGroups.push_back(g);
                    }

                    va_end(list);
                };
                std::list<AchievementGroup *> &getAll() { return _achievementGroups; };

            private:
                std::list<AchievementGroup *> _achievementGroups;
        };

        std::list<AchievementGroup *> getGameAchievements();
    }
}

#endif
