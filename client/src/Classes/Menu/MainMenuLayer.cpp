#include "MainMenuLayer.h"
#include "LevelSelectLayer.h"
#include "../Common/Primitives/ConnectionType.h"

MainMenuLayer::MainMenuLayer()
{

}

MainMenuLayer::~MainMenuLayer()
{

}

Scene* MainMenuLayer::scene()
{
	Scene * scene = NULL;
    // 'scene' is an autorelease object
    scene = Scene::create();
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
    if (!Layer::init())
        return false;

    Size visibleSize = Director::sharedDirector()->getVisibleSize();
    
    ccMenuCallback callbackGame = std::bind(&MainMenuLayer::newGame, this, this);
    MenuItem *newGameItem = MenuItemImage::create(
        "menu/new_game.png",
        "menu/new_game.png",
        callbackGame
    );

    ccMenuCallback callbackLevels = std::bind(&MainMenuLayer::showLevels, this, this);
    MenuItem *levelsItem = MenuItemImage::create(
        "menu/levels.png",
        "menu/levels.png",
        callbackLevels
    );

    //Menu* menu = Menu::create(newGameItem, levelsItem, NULL);
    Menu* menu = Menu::create(levelsItem, NULL);

    newGameItem->setPosition(ccp(0, 0));
    //levelsItem->setPosition(ccp(0, -150));
    levelsItem->setPosition(ccp(0, 0));

    this->addChild(menu, 1);

    menu->setPosition(
        ccp(
            visibleSize.width/2,
            visibleSize.height - 200
        )
    );

    //this->setTouchEnabled(true);
    this->setKeyboardEnabled(true);

    return true;
}

void MainMenuLayer::newGame(Object *sender)
{
    CCLog("new game from main menu");

    MenuSelections *ms = MenuSelections::getInstance();
    ms->setLevelName( "level_01.tmx" );
    ms->setNumPlayers( 2 );
    ms->setConnection( Bomber::Common::WIDE_CON );

    Scene *pScene = GameplayScene::scene();
    Director::sharedDirector()->replaceScene(pScene);
}

void MainMenuLayer::showLevels(Object *sender)
{
    CCLog("level select from main menu");
    Scene *pScene = LevelSelectLayer::scene();
    Director::sharedDirector()->replaceScene(pScene);
}

void MainMenuLayer::registerWithTouchDispatcher()
{
    // TouchDispatcher::sharedDispatcher()->addTargetedDelegate(this,0,true);
    Director::sharedDirector()->getTouchDispatcher()->addStandardDelegate(this,0);
}

