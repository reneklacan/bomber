#include "MainMenuLayer.h"
#include "../GameplayScene.h"

MainMenuLayer::MainMenuLayer()
{

}

MainMenuLayer::~MainMenuLayer()
{

}

CCScene* MainMenuLayer::scene()
{
	CCScene * scene = NULL;
    // 'scene' is an autorelease object
    scene = CCScene::create();
    if (!scene)
        return NULL;

    // 'layer' is an autorelease object
    MainMenuLayer *layer = MainMenuLayer::create();
    if (!layer)
        return NULL;
    ;
    // add layer as a child to scene
    scene->addChild(layer);

	// return the scene
	return scene;
}

bool MainMenuLayer::init()
{
    if (!CCLayer::init())
        return false;

    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    
    CCMenuItem *newGameItem = CCMenuItemImage::create(
            "menu/new_game.png",
            "menu/new_game.png",
            this,
            menu_selector(MainMenuLayer::newGame) 
    );
    CCMenuItem *levelsItem = CCMenuItemImage::create(
            "menu/levels.png",
            "menu/levels.png",
            this,
            menu_selector(MainMenuLayer::newGame) 
    );
    CCMenu* menu = CCMenu::create(newGameItem, levelsItem, NULL);

    newGameItem->setPosition(ccp(0, 0));
    levelsItem->setPosition(ccp(0, -150));

    this->addChild(menu, 1);

    menu->setPosition(
            ccp(
                visibleSize.width/2,
                visibleSize.height - 200
            )
    );

    this->setTouchEnabled(true);

    return true;
}

void MainMenuLayer::newGame(CCObject *sender)
{
    CCLog("new game from main menu");
    CCScene *pScene = GameplayScene::scene();
    CCDirector::sharedDirector()->replaceScene(pScene);
}

void MainMenuLayer::registerWithTouchDispatcher()
{
    // CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this,0,true);
    CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate(this,0);
}

