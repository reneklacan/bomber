
#include <stdio.h>

#include "Achievements.h"

using namespace Bomber::Backend;

AchievementCondition::AchievementCondition(
        TAchievConditionType type,
        const char *kind,
        unsigned int amount,
        unsigned int timeLimit
)
{
    _type = type;
    _kind = kind;
    _amount = amount;
    _timeLimit = timeLimit;
}

bool AchievementCondition::evaluate(Statistics *statistics)
{
    switch (_type)
    {
        case BOMBS:
            if (statistics->getBombSpawns() == _amount)
            {
                return true;
            }
            break;

        case KILLS:
            return false;

        default:
            printf("AchievementCondition::evaluate unknown type: %d\n", _type);
            return false;
    }

    return false;
}

AchievementOne::AchievementOne(
        const char *act,
        const char *level,
        const char *title,
        const char *description,
        bool evalOnEnd,
        std::list<AchievementCondition> conditions
)
{
    _act = act;
    _level = level;
    _title = title;
    _description = description;
    _evalOnEnd = evalOnEnd;
    _conditions = conditions;
}

bool AchievementOne::isComplete(Statistics *statistics)
{
    for (auto condition : _conditions)
    {
        if (!condition.evaluate(statistics))
        {
            return false;
        }
    }
    return true;
}

AchievementGroup::AchievementGroup(std::list<Achievement> achievements)
{

}
