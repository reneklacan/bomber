
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
    _allAchievements = getGameAchievements();
}

void AchievementContainer::checkAll(Statistics *statistics)
{
    for (auto object : _allAchievements)
    {
        if (object->isGroup())
        {
            auto group = (AchievementGroup *) object;

            for (Achievement *object : group->getAchievements())
            {
                auto achievement = (AchievementOne *) object;

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
        else
        {
            auto achievement = (AchievementOne *) object;

            if (achievement->isComplete(statistics))
            {
                _newUnlocked.push_back(achievement);
            }
        }
    }
}

std::list<AchievementOne *> AchievementContainer::getNewUnlocked()
{
    std::list<AchievementOne *> unlocked;

    while (_newUnlocked.size())
    {
        unlocked.push_back(_newUnlocked.front());
        _newUnlocked.pop_front();
    }

    return unlocked;
}
