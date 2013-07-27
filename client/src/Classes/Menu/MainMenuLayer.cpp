#include "MainMenuLayer.h"
#include "../GameplayScene.h"

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
    
    // TODO: fix deprecated warning
    MenuItem *newGameItem = MenuItemImage::create(
            "menu/new_game.png",
            "menu/new_game.png",
            this,
            menu_selector(MainMenuLayer::newGame) 
    );
    MenuItem *levelsItem = MenuItemImage::create(
            "menu/levels.png",
            "menu/levels.png",
            this,
            menu_selector(MainMenuLayer::newGame) 
    );
    Menu* menu = Menu::create(newGameItem, levelsItem, NULL);

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

void MainMenuLayer::newGame(Object *sender)
{
    CCLog("new game from main menu");
    Scene *pScene = GameplayScene::scene();
    Director::sharedDirector()->replaceScene(pScene);
}

void MainMenuLayer::registerWithTouchDispatcher()
{
    // TouchDispatcher::sharedDispatcher()->addTargetedDelegate(this,0,true);
    Director::sharedDirector()->getTouchDispatcher()->addStandardDelegate(this,0);
}

