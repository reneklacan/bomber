#include "PlayersSelectLayer.h"

//
Scene* PlayersSelectLayer::scene()
{
    Scene * scene = NULL;
    // 'scene' is an autorelease object
    scene = Scene::create();
    if (!scene)
        return NULL;

    // 'layer' is an autorelease object
    PlayersSelectLayer *layer = PlayersSelectLayer::create();
    if (!layer)
        return NULL;
    ;
    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

//
bool PlayersSelectLayer::init()
{
    if (!Layer::init())
        return false;

    Size visibleSize = Director::sharedDirector()->getVisibleSize();
    Menu* menu = Menu::create();

    // Add all possibilities
    int position = 0;
    for(unsigned int i = 1; i <= 2; i++ )
    {
        std::string label = std::to_string(i);
        label += (i == 1) ? " Player" : " Players";

        ccMenuCallback callback = std::bind(&PlayersSelectLayer::newGame, this, this, i);

        MenuItemFont *newLevel = new MenuItemFont();
        newLevel->initWithString(
                label.c_str(),
                callback
        );
        newLevel->setPosition(ccp(0, position));
        menu->addChild(newLevel);
        position -= 50;
    }

    // Add menu to layer
    this->addChild(menu, 1);

    menu->setPosition(
            ccp(
                visibleSize.width/2,
                visibleSize.height - 100
            )
    );

    this->setTouchEnabled(true);

    return true;
}

//
void PlayersSelectLayer::newGame(Object *sender, unsigned int numPlayers)
{
    CCLog("new game from players menu");

    using namespace Bomber::Frontend;
    MenuSelections *ms = MenuSelections::getInstance();
    ms->setNumPlayers( numPlayers );

    Scene *pScene = GameplayScene::scene();
    Director::sharedDirector()->replaceScene(pScene);
}

//
void PlayersSelectLayer::registerWithTouchDispatcher()
{
    // TouchDispatcher::sharedDispatcher()->addTargetedDelegate(this,0,true);
    Director::sharedDirector()->getTouchDispatcher()->addStandardDelegate(this,0);
}