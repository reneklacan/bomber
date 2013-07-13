
#include <stdio.h>
#include <stdarg.h>

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

Achievement::Achievement(
        const char *act,
        const char *level,
        const char *title,
        const char *description,
        bool evalOnEnd
)
{
    _unlocked = false;
    _act = act;
    _level = level;
    _title = title;
    _description = description;
    _evalOnEnd = evalOnEnd;
}

Achievement::Achievement(
        const char *act,
        const char *level,
        const char *title,
        const char *description,
        bool evalOnEnd,
        AchievementCondition *condition,
        ...
)
{
    _unlocked = false;
    _act = act;
    _level = level;
    _title = title;
    _description = description;
    _evalOnEnd = evalOnEnd;

    this->addCondition(condition);

    va_list list;
    va_start(list, condition);

    while (true)
    {
        AchievementCondition *c = va_arg(list, AchievementCondition *);

        if (c == nullptr)
            break;

        this->addCondition(c);
    }

    va_end(list);
}

void Achievement::addCondition(AchievementCondition *condition)
{
    _conditions.push_back(condition);
}

bool Achievement::isComplete(Statistics *statistics)
{
    for (auto condition : _conditions)
    {
        if (!condition->evaluate(statistics))
        {
            return false;
        }
    }
    _unlocked = true;
    return true;
}

AchievementGroup::AchievementGroup()
{

}

AchievementGroup::AchievementGroup(Achievement *achievement, ...)
{
    this->add(achievement);

    va_list list;
    va_start(list, achievement);

    while (true)
    {
        Achievement *a = va_arg(list, Achievement *);

        if (a == nullptr)
            break;

        this->add(a);
    }

    va_end(list);
}

void AchievementGroup::add(Achievement *achievement)
{
    _achievements.push_back(achievement);
}