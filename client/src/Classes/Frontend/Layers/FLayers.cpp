#include "FLayers.h"

using namespace Bomber::Frontend;

Layer *Layers::getFinishLevelLayer(Statistics *statistics, std::vector<ccMenuCallback> callbacks)
{
	Size visibleSize = Director::sharedDirector()->getVisibleSize();

    // Create new layer
    LayerColor *lc = new LayerColor();
    int lcWidth = (int)visibleSize.width*0.75;
    int lcHeight = (int)visibleSize.height;
    lc->initWithColor( ccc4(10, 10, 10, 180), lcWidth, lcHeight);
    lc->setPosition(
        visibleSize.width/2 - lcWidth/2,
        visibleSize.height/4.5  // dunno why it works
    );

    std::string stars = "";
    unsigned int gainedStars = statistics->getStars();
    stars += std::to_string( gainedStars );
    stars += " star";
    if(gainedStars > 1)
    {
        stars += "s";
    }
    stars += " out of 5";
    LabelTTF* stats = LabelTTF::create(
        stars.c_str(),
        "Helvetica",
        24,
        CCSizeMake(lcWidth, 24),
        kTextAlignmentCenter,
        kVerticalTextAlignmentTop
    );
    stats->setPosition(ccp(lcWidth/2, lcHeight/2+290));
    lc->addChild(stats, 1);

    std::string levelTime = "Time: ";
    levelTime += std::to_string( statistics->getLevelTimer() );
    levelTime += " seconds";
    stats = LabelTTF::create(
        levelTime.c_str(),
        "Helvetica",
        24,
        CCSizeMake(lcWidth, 24),
        kTextAlignmentCenter,
        kVerticalTextAlignmentTop
    );
    stats->setPosition(ccp(lcWidth/2, lcHeight/2+260));
    lc->addChild(stats, 1);

    std::string killedMonsters = "Monsters Killed: ";
    killedMonsters += std::to_string( statistics->getKilledMonsters() );
    stats = LabelTTF::create(
        killedMonsters.c_str(),
        "Helvetica",
        24,
        CCSizeMake(lcWidth, 24),
        kTextAlignmentCenter,
        kVerticalTextAlignmentTop
    );
    stats->setPosition(ccp(lcWidth/2, lcHeight/2+230));
    lc->addChild(stats, 1);

    std::string bombSpawns = "Bombs spawned: ";
    bombSpawns += std::to_string( statistics->getBombSpawns() );
    stats = LabelTTF::create(
        bombSpawns.c_str(),
        "Helvetica",
        24,
        CCSizeMake(lcWidth, 24),
        kTextAlignmentCenter,
        kVerticalTextAlignmentTop
    );
    stats->setPosition(ccp(lcWidth/2, lcHeight/2+200));
    lc->addChild(stats, 1);

    std::string achievementUnlocks = "Achievements Earned: ";
    achievementUnlocks += std::to_string( statistics->getAchievementUnlocks() );
    stats = LabelTTF::create(
        achievementUnlocks.c_str(),
        "Helvetica",
        24,
        CCSizeMake(lcWidth, 24),
        kTextAlignmentCenter,
        kVerticalTextAlignmentTop
    );
    stats->setPosition(ccp(lcWidth/2, lcHeight/2+170));
    lc->addChild(stats, 1);

    std::string takenBuffs = "Enchantments Taken: ";
    takenBuffs += std::to_string( statistics->getTakenBuffs() );
    stats = LabelTTF::create(
        takenBuffs.c_str(),
        "Helvetica",
        24,
        CCSizeMake(lcWidth, 24),
        kTextAlignmentCenter,
        kVerticalTextAlignmentTop
    );
    stats->setPosition(ccp(lcWidth/2, lcHeight/2+140));
    lc->addChild(stats, 1);

    std::string usedLevers = "Levers Used: ";
    usedLevers += std::to_string( statistics->getUsedLevers() );
    stats = LabelTTF::create(
        usedLevers.c_str(),
        "Helvetica",
        24,
        CCSizeMake(lcWidth, 24),
        kTextAlignmentCenter,
        kVerticalTextAlignmentTop
    );
    stats->setPosition(ccp(lcWidth/2, lcHeight/2+110));
    lc->addChild(stats, 1);

    std::string teleportations = "Teleports Used: ";
    teleportations += std::to_string( statistics->getTeleportations() );
    stats = LabelTTF::create(
        teleportations.c_str(),
        "Helvetica",
        24,
        CCSizeMake(lcWidth, 24),
        kTextAlignmentCenter,
        kVerticalTextAlignmentTop
    );
    stats->setPosition(ccp(lcWidth/2, lcHeight/2+80));
    lc->addChild(stats, 1);

    std::string finalScore = "FINAL SCORE: ";
    finalScore += std::to_string( statistics->getFinalScore() );
    stats = LabelTTF::create(
        finalScore.c_str(),
        "Helvetica",
        24,
        CCSizeMake(lcWidth, 24),
        kTextAlignmentCenter,
        kVerticalTextAlignmentTop
    );
    stats->setPosition(ccp(lcWidth/2, lcHeight/2+50));
    lc->addChild(stats, 1);

    // Create menu
    Menu* menu = Menu::create();

    // Back
    MenuItemFont *backToMenu = new MenuItemFont();
    backToMenu->initWithString(
        "Back to Levels",
        callbacks[0]
    );
    backToMenu->setPosition(ccp(0, 0));
    menu->addChild(backToMenu);

    // Retry
    MenuItemFont *retryLevel = new MenuItemFont();
    retryLevel->initWithString(
        "Retry",
        callbacks[1]
    );
    retryLevel->setPosition(ccp(0, -30));
    menu->addChild(retryLevel);

    menu->setPosition(
        ccp(
            lcWidth/2,
            lcHeight/2
        )
    );

    // Add menu to the new layer
    lc->addChild(menu, 1);

    return lc;
}