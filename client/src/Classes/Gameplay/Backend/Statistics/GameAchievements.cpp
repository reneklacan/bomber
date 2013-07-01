
#include "GameAchievements.h"

#define AchievementList(...) std::list<Achievement *>({ __VA_ARGS__ })
#define ConditionList(...) std::list<AchievementCondition>({ __VA_ARGS__ })
#define Group(...) new AchievementGroup(AchievementList({ __VA_ARGS__ }))
#define Achievement(...) new AchievementOne( __VA_ARGS__ )
#define Condition AchievementCondition
#define None nullptr
#define AchievementOne new AchievementOne

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
            "Act 1", // act
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

std::list<Achievement *> Bomber::Backend::getGameAchievements()
{
    return gameAchievements;
}
