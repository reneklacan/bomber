
#include "GameAchievements.h"

#define Condition AchievementCondition
#define None nullptr

using namespace Bomber::Backend;

std::list<AchievementGroup *> Bomber::Backend::getGameAchievements()
{
    GameAchievements *gameAchievements = new GameAchievements(
        new AchievementGroup(
            new Achievement(
                None, // act
                None, // level
                "Newcomer", // title
                "Kill your first mob", // descriptopn
                false, // evaluate on the end of the game/act/level

                new AchievementCondition(
                    KILLS, // type
                    None, // kind
                    1, // amount
                    0 // time limit
                ),
                nullptr
            ),
            nullptr
        ),
        new AchievementGroup(
            new Achievement(
                None, // act
                None, // level
                "Pump it", // title
                "Get your first buff", // descriptopn
                false, // evaluate on the end of the game/act/level

                new AchievementCondition(
                    EFFECTS, // type
                    None, // kind
                    1, // amount
                    0 // time limit
                ),
                nullptr
            ),
            nullptr
        ),
        new AchievementGroup(
            new Achievement(
                None, // act
                None, // level
                "Double kill", // title
                "Kill two mobs with one bomb", // descriptopn
                false, // evaluate on the end of the game/act/level

                new AchievementCondition(
                    KILL_STREAKS, // type
                    None, // kind
                    2, // amount
                    0 // time limit
                ),
                nullptr
            ),
            new Achievement(
                None, // act
                None, // level
                "Triple kill", // title
                "Kill three mobs with one bomb", // descriptopn
                false, // evaluate on the end of the game/act/level

                new AchievementCondition(
                    KILL_STREAKS, // type
                    None, // kind
                    3, // amount
                    0 // time limit
                ),
                nullptr
            ),
            nullptr
        ),
        new AchievementGroup(
            new Achievement(
                None, // act
                None, // level
                "Bombeeeer", // title
                "Plant 5 bomb in overall", // descriptopn
                false, // evaluate on the end of the game/act/level

                new AchievementCondition(
                    BOMBS, // type
                    None, // kind
                    5, // amount
                    0 // time limit
                ),
                nullptr
            ),
            new Achievement(
                None, // act
                None, // level
                "Bombeeeer 2", // title
                "Plant 10 bomb in overall", // descriptopn
                false, // evaluate on the end of the game/act/level

                new AchievementCondition(
                    BOMBS, // type
                    None, // kind
                    10, // amount
                    0 // time limit
                ),
                nullptr
            ),
            nullptr
        ),
        new AchievementGroup(
            new Achievement(
                "Act 1", // act
                "Level 1", // level
                "Fast Ghost killer", // title
                "Kill 10 ghost in a one minute", // descriptopn
                true, // evaluate on the end of the game/act/level

                new AchievementCondition(
                    KILLS, // type
                    "Ghost", // kind
                    10, // amount
                    60 // time limit
                ),
                nullptr
            ),
            nullptr
        ),
        nullptr
    );

    return gameAchievements->getAll();
}
