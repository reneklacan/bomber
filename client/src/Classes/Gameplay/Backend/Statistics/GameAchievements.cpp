
#include "GameAchievements.h"

#define Condition AchievementCondition
#define None nullptr

using namespace Bomber::Backend;

std::list<AchievementObject *> Bomber::Backend::getGameAchievements()
{
    std::list<AchievementObject *> gameAchievements;

    AchievementGroup *bombAchievementGroup = new AchievementGroup();

    Achievement *bombAchievement5 = new Achievement(
            None, // act
            None, // level
            "Bombeeeer", // title
            "Plant 5 bomb in overall", // descriptopn
            false // evaluate on the end of the game/act/level
    );
    bombAchievement5->addCondition(
            AchievementCondition(
                BOMBS, // type
                None, // kind
                5, // amount
                0 // time limit
            )
    );
    Achievement *bombAchievement10 = new Achievement(
            None, // act
            None, // level
            "Bombeeeer 2", // title
            "Plant 10 bomb in overall", // descriptopn
            false // evaluate on the end of the game/act/level
    );
    bombAchievement10->addCondition(
            Condition(
                BOMBS, // type
                None, // kind
                10, // amount
                0 // time limit
            )
    );

    bombAchievementGroup->add(bombAchievement5);
    bombAchievementGroup->add(bombAchievement10);

    AchievementGroup *killAchievementGroup = new AchievementGroup();

    Achievement *killAchievement10in60 = new Achievement(
            "Act 1", // act
            "Level 1", // level
            "Fast Ghost killer", // title
            "Kill 10 ghost in a one minute", // descriptopn
            true // evaluate on the end of the game/act/level
    );
    killAchievement10in60->addCondition(
            Condition(
                KILLS, // type
                "Ghost", // kind
                10, // amount
                60 // time limit
            )
    );

    killAchievementGroup->add(killAchievement10in60);
    
    gameAchievements.push_back(bombAchievementGroup);
    gameAchievements.push_back(killAchievementGroup);

    return gameAchievements;
}
