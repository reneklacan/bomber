#include "FLayers.h"

using namespace Bomber::Frontend;

Layer *Layers::getFinishLevelLayer(Statistics *statistics, std::vector<ccMenuCallback> callbacks)
{
	Size visibleSize = Director::sharedDirector()->getVisibleSize();

    // Create new layer
    LayerColor *lc = new LayerColor();
    int lcWidth = (int)visibleSize.width*0.75;
    int lcHeight = (int)visibleSize.height;
    lc->initWithColor( ccc4(10, 10, 10, 220), lcWidth, lcHeight);
    lc->setPosition(
        visibleSize.width/2 - lcWidth/2,
        visibleSize.height/4.5  // dunno why it works
    );

    // Proportions
    int pHOffset = (int)(lcHeight * 0.05);
    int pWOffset = (int)(lcWidth * 0.05);
    unsigned int pFontSize = 26;
    std::string pFontName = "fonts/culturalstupidity.ttf";
    unsigned int borderSize = 3.5;
    unsigned int borderPadding = 5*borderSize;
    int leftColumnX = lcWidth/2+pWOffset;
    int rihtColumnX = lcWidth+pWOffset;
    std::string starIcon = "other/star.png";

    // Stars
    unsigned int gainedStars = statistics->getStars();
    Sprite *starImage = NULL;
    for(unsigned int i = 0; i < 5; i++)
    {
        starImage = Sprite::create(starIcon.c_str());
        starImage->setAnchorPoint(ccp(0,0));
        starImage->setScale(0.2f);
        Rect starRect = starImage->boundingBox();
        int starOffset = (starRect.getMaxX() - starRect.getMinX()) * 1.2;
        int starRadius = (starRect.getMaxX() - starRect.getMinX()) * 0.6;
        starImage->setPosition(ccp(lcWidth/2 + (i-3)*starOffset + starRadius, lcHeight/2+5.5*pHOffset));
        if(i > gainedStars-1)
        {
            starImage->setOpacity(50);
        }
        lc->addChild(starImage, 1);
    }


    // Labels and Buttons
    std::string stars = "";
    stars += std::to_string( gainedStars );
    stars += " star";
    if(gainedStars > 1)
    {
        stars += "s";
    }
    stars += " out of 5";
    LabelTTF* stats = LabelTTF::create(
        stars.c_str(),
        pFontName.c_str(),
        pFontSize,
        CCSizeMake(lcWidth, pFontSize),
        kTextAlignmentCenter,
        kVerticalTextAlignmentTop
    );
    stats->setPosition(ccp(lcWidth/2, lcHeight/2+4.5*pHOffset));
    lc->addChild(stats, 1);

    std::string levelTime = "time: ";
    levelTime += std::to_string( statistics->getLevelTimer() );
    levelTime += " seconds";
    stats = LabelTTF::create(
        levelTime.c_str(),
        pFontName.c_str(),
        pFontSize,
        CCSizeMake(lcWidth, pFontSize),
        kTextAlignmentLeft,
        kVerticalTextAlignmentTop
    );
    stats->setPosition(ccp(leftColumnX, lcHeight/2+2*pHOffset));
    lc->addChild(stats, 1);

    std::string killedMonsters = "monsters killed: ";
    killedMonsters += std::to_string( statistics->getKilledMonsters() );
    stats = LabelTTF::create(
        killedMonsters.c_str(),
        pFontName.c_str(),
        pFontSize,
        CCSizeMake(lcWidth, pFontSize),
        kTextAlignmentLeft,
        kVerticalTextAlignmentTop
    );
    stats->setPosition(ccp(leftColumnX, lcHeight/2+0.5*pHOffset));
    lc->addChild(stats, 1);

    std::string bombSpawns = "bombs spawned: ";
    bombSpawns += std::to_string( statistics->getBombSpawns() );
    stats = LabelTTF::create(
        bombSpawns.c_str(),
        pFontName.c_str(),
        pFontSize,
        CCSizeMake(lcWidth, pFontSize),
        kTextAlignmentLeft,
        kVerticalTextAlignmentTop
    );
    stats->setPosition(ccp(leftColumnX, lcHeight/2-1*pHOffset));
    lc->addChild(stats, 1);

    std::string achievementUnlocks = "achievements: ";
    achievementUnlocks += std::to_string( statistics->getAchievementUnlocks() );
    stats = LabelTTF::create(
        achievementUnlocks.c_str(),
        pFontName.c_str(),
        pFontSize,
        CCSizeMake(lcWidth, pFontSize),
        kTextAlignmentLeft,
        kVerticalTextAlignmentTop
    );
    stats->setPosition(ccp(leftColumnX, lcHeight/2-2.5*pHOffset));
    lc->addChild(stats, 1);

    std::string takenBuffs = "enchantments: ";
    takenBuffs += std::to_string( statistics->getTakenBuffs() );
    stats = LabelTTF::create(
        takenBuffs.c_str(),
        pFontName.c_str(),
        pFontSize,
        CCSizeMake(lcWidth, pFontSize),
        kTextAlignmentLeft,
        kVerticalTextAlignmentTop
    );
    stats->setPosition(ccp(leftColumnX, lcHeight/2-4*pHOffset));
    lc->addChild(stats, 1);

    std::string destroyedObstacles = "destroyed blocks: ";
    destroyedObstacles += std::to_string( statistics->getDestroyedObstacles() );
    stats = LabelTTF::create(
        destroyedObstacles.c_str(),
        pFontName.c_str(),
        pFontSize,
        CCSizeMake(lcWidth, pFontSize),
        kTextAlignmentLeft,
        kVerticalTextAlignmentTop
    );
    stats->setPosition(ccp(rihtColumnX, lcHeight/2+2*pHOffset));
    lc->addChild(stats, 1);

    std::string usedLevers = "levers used: ";
    usedLevers += std::to_string( statistics->getUsedLevers() );
    stats = LabelTTF::create(
        usedLevers.c_str(),
        pFontName.c_str(),
        pFontSize,
        CCSizeMake(lcWidth, pFontSize),
        kTextAlignmentLeft,
        kVerticalTextAlignmentTop
    );
    stats->setPosition(ccp(rihtColumnX, lcHeight/2+0.5*pHOffset));
    lc->addChild(stats, 1);

    std::string teleportations = "teleports used: ";
    teleportations += std::to_string( statistics->getTeleportations() );
    stats = LabelTTF::create(
        teleportations.c_str(),
        pFontName.c_str(),
        pFontSize,
        CCSizeMake(lcWidth, pFontSize),
        kTextAlignmentLeft,
        kVerticalTextAlignmentTop
    );
    stats->setPosition(ccp(rihtColumnX, lcHeight/2-1*pHOffset));
    lc->addChild(stats, 1);

    std::string ranDistance = "distance: ";
    ranDistance += std::to_string( statistics->getRanUnits() );
    ranDistance += " m";
    stats = LabelTTF::create(
        ranDistance.c_str(),
        pFontName.c_str(),
        pFontSize,
        CCSizeMake(lcWidth, pFontSize),
        kTextAlignmentLeft,
        kVerticalTextAlignmentTop
    );
    stats->setPosition(ccp(rihtColumnX, lcHeight/2-2.5*pHOffset));
    lc->addChild(stats, 1);

    std::string finalScore = "FINAL SCORE: ";
    finalScore += std::to_string( statistics->getFinalScore() );
    stats = LabelTTF::create(
        finalScore.c_str(),
        pFontName.c_str(),
        pFontSize,
        CCSizeMake(lcWidth, pFontSize),
        kTextAlignmentLeft,
        kVerticalTextAlignmentTop
    );
    stats->setPosition(ccp(rihtColumnX, lcHeight/2-4*pHOffset));
    lc->addChild(stats, 1);

    // Create menu
    Menu* menu = Menu::create();

    // Continue
    MenuItemFont *backToMenu = new MenuItemFont();
    backToMenu->initWithString(
        "NEXT LEVEL",
        callbacks[0]
    );
    backToMenu->setPosition(
        ccp(
            lcWidth/2-5*pWOffset, 
            -lcHeight/2+2*pHOffset
        )
    );
    backToMenu->setFontNameObj(pFontName.c_str());
    backToMenu->setFontSizeObj(pFontSize);
    menu->addChild(backToMenu, 10);

    // Retry
    MenuItemFont *retryLevel = new MenuItemFont();
    retryLevel->initWithString(
        "RETRY LEVEL",
        callbacks[1]
    );
    retryLevel->setPosition(
        ccp(
            -lcWidth/2+5*pWOffset, 
            -lcHeight/2+2*pHOffset
        )
    );
    retryLevel->setFontNameObj(pFontName.c_str());
    retryLevel->setFontSizeObj(pFontSize);
    menu->addChild(retryLevel, 10);

    // Borders
    auto dr = DrawNode::create();

    // Border for Continue
    Point *ccPoints = Shapes::getBorderBox(
        backToMenu->getPosition(),
        backToMenu->boundingBox(),
        borderPadding
    );
    dr->DrawNode::drawPolygon(
        ccPoints,
        4,
        ccc4f(0.0, 0.0, 0.0, 0.5),
        borderSize,
        ccc4f(0.8, 0.6, 0.4, 0.4)
    );
    menu->addChild(dr);

    // Border for Retry
    ccPoints = Shapes::getBorderBox(
        retryLevel->getPosition(),
        retryLevel->boundingBox(),
        borderPadding
    );
    dr->DrawNode::drawPolygon(
        ccPoints,
        4,
        ccc4f(0.0, 0.0, 0.0, 0.5),
        borderSize,
        ccc4f(0.8, 0.6, 0.4, 0.4)
    );
    menu->addChild(dr);

    // Position
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

void Layers::createControlButtonLayer(std::vector<SEL_MenuHandler> callbacks, Layer* layer)
{
    // Quit Button
    ControlButton *cbQuit = new ControlButton(
        0,
        "buttons/button_black_power_64.png",
        layer,
        callbacks[0]
    );
    ButtonLayer::getInstance()->addToControls(cbQuit);

    // Pause/Resume Button
    ControlButton *cbPause = new ControlButton(
        0,
        "buttons/button_black_pause_64.png",
        layer,
        callbacks[1]
    );
    ButtonLayer::getInstance()->addToControls(cbPause);

    // Reset Button
    ControlButton *cbReset = new ControlButton(
        0,
        "buttons/button_black_repeat_64.png",
        layer,
        callbacks[2]
    );
    ButtonLayer::getInstance()->addToControls(cbReset);
}