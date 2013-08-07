
#include <stdio.h>

#include "AchievementContainer.h"

using namespace Bomber::Backend;

AchievementContainer* AchievementContainer::_instance = nullptr;

AchievementContainer* AchievementContainer::getInstance()
{
    if (_instance == nullptr)
    {
        _instance = new AchievementContainer();
    }
    return _instance;
}

AchievementContainer::AchievementContainer()
{
    _allAchievementGroups = getGameAchievements();

    for (auto group : _allAchievementGroups)
    {
        for (auto achievement : group->getAchievements())
        {
            for (auto condition : achievement->getConditions())
            {
                _achievementGroupMap[condition->getType()].insert(group);
            }
        }
    }
}

void AchievementContainer::checkType(TAchievConditionType type, Statistics *statistics)
{
    for (AchievementGroup *group : _achievementGroupMap[type])
    {
        for (Achievement *achievement : group->getAchievements())
        {
            if (achievement->isUnlocked())
                continue;

            if (achievement->isComplete(statistics))
            {
                _newUnlocked.push_back(achievement);
            }
            else
            {
                break;
            }
        }
    }
}

void AchievementContainer::checkAll(Statistics *statistics)
{
    for (AchievementGroup *group : _allAchievementGroups)
    {
        for (Achievement *achievement : group->getAchievements())
        {
            if (achievement->isUnlocked())
                continue;

            if (achievement->isComplete(statistics))
            {
                _newUnlocked.push_back(achievement);
            }
            else
            {
                break;
            }
        }
    }
}

std::list<Achievement *> AchievementContainer::getNewUnlocked()
{
    std::list<Achievement *> unlocked;

    while (_newUnlocked.size())
    {
        unlocked.push_back(_newUnlocked.front());
        _newUnlocked.pop_front();
    }

    return unlocked;
}
