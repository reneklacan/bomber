#include "FLayers.h"

using namespace Bomber::Frontend;

Layer *Layers::getFinishLevelLayer(Statistics *statistics, std::vector<ccMenuCallback> callbacks)
{
	Size visibleSize = Director::sharedDirector()->getVisibleSize();

    // Create new layer
    LayerColor *lc = new LayerColor();
    int lcWidth = (int)visibleSize.width*0.75;
    int lcHeight = (int)visibleSize.height*0.60;
    lc->initWithColor( ccc4(10, 10, 10, 180), lcWidth, lcHeight);
    lc->setPosition(
        visibleSize.width/2 - lcWidth/2,
        visibleSize.height/2 - lcHeight/8
    );

    std::string levelTime = "Time: ";
    levelTime += std::to_string( statistics->getLevelTimer() );
    levelTime += " seconds";
    LabelTTF* stats = LabelTTF::create(
        levelTime.c_str(),
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