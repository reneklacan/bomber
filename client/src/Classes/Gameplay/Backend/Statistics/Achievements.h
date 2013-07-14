#ifndef __BOMBER_BACKEND_ACHIEVEMENTS
#define __BOMBER_BACKEND_ACHIEVEMENTS

#include <list>
#include "Statistics.h"

namespace Bomber
{
    namespace Backend
    {
        enum TAchievConditionType
        {
            BOMBS,
            KILLS,
            KILL_STREAKS,
            EFFECTS,
            SKILL,
        };

        class AchievementCondition
        {
            public:
                AchievementCondition(
                        TAchievConditionType type,
                        const char *kind,
                        unsigned int amount,
                        unsigned int timeLimit
                );
                bool evaluate(Statistics *statistics);

            private:
                TAchievConditionType _type;
                const char *_kind;
                unsigned int _amount;
                unsigned int _timeLimit;
        };

        class Achievement
        {
            public:
                Achievement(
                        const char *act,
                        const char *level,
                        const char *title,
                        const char *description,
                        bool evalOnEnd,
                        AchievementCondition *condition,
                        ...
                );
                void addCondition(AchievementCondition *condition);
                bool isComplete(Statistics *statistics);
                inline virtual bool isGroup() { return false; }
                inline virtual bool isUnlocked() { return _unlocked; }

            private:
                bool _unlocked;
                const char *_act;
                const char *_level;
                SYNTHESIZE(const char *, _title, Title);
                SYNTHESIZE(const char *, _description, Description);
                bool _evalOnEnd;
                std::list<AchievementCondition *> _conditions;
        };

        class AchievementGroup
        {
            public:
                AchievementGroup();
                AchievementGroup(Achievement *object, ...);
                void add(Achievement *object);

            private:
                SYNTHESIZE_READONLY(std::list<Achievement *>, _achievements, Achievements);
        };
    }
}

#endif
