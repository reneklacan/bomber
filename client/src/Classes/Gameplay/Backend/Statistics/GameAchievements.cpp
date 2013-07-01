
#include "Achievements.h"

using namespace Bomber::Backend;

auto gameAchievements = AchievementList(
        Group(
            AchievementOne(
                None, // act
                None, // level
                "Bombeeeer", // title
                "Plant 5 bomb in overall", // descriptopn
                false, // evaluate on the end of the game/act/level
                ConditionList(
                    Condition(
                        BOMBS, // type
                        None, // kind
                        5, // amount
                        0 // time limit
                    ),
                )
            ),
            AchievementOne(
                None, // act
                None, // level
                "Bombeeeer 2", // title
                "Plant 10 bomb in overall", // descriptopn
                false, // evaluate on the end of the game/act/level
                ConditionList(
                    Condition(
                        BOMBS, // type
                        None, // kind
                        10, // amount
                        0 // time limit
                    ),
                )
            ),
        ),
        AchievementOne(
            "Act 1", // any
            "Level 1", // level
            "Fast Ghost killer", // title
            "Kill 10 ghost in a one minute", // descriptopn
            true, // evaluate on the end of the game/act/level
            ConditionList(
                Condition(
                    KILLS, // type
                    "Ghost", // kind
                    10, // amount
                    60 // time limit
                ),
            )
        ),
);

static std::list<Achievement> getGameAchievements()
{
    return gameAchievements;
}
