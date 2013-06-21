#include "GameplayScene.h"
#include "GameOverScene.h"
//#include "SimpleAudioEngine.h"
//#include "Gameplay/Map/Bomb.h"

using namespace cocos2d;

GameplayScene::~GameplayScene()
{
}

GameplayScene::GameplayScene()
:_levelLayer(NULL)
{
}

CCScene* GameplayScene::scene()
{
	CCScene * scene = NULL;
    // 'scene' is an autorelease object
    scene = CCScene::create();
    if (!scene)
        return NULL;

    // 'layer' is an autorelease object
    GameplayScene *layer = GameplayScene::create();
    if (!layer)
        return NULL;
    ;
    // add layer as a child to scene
    scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool GameplayScene::init()
{
    _levelLayer = LevelLayer::create();
    this->addChild(_levelLayer);

    // Create a "close" menu item with close icon, it's an auto release object.
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
            "CloseNormal.png",
            "CloseSelected.png",
            this,
            menu_selector(GameplayScene::menuCloseCallback)
    );
    if (!pCloseItem)
        return false;

    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    pCloseItem->setPosition(
            ccp(
                origin.x + visibleSize.width - pCloseItem->getContentSize().width/2,
                origin.y + pCloseItem->getContentSize().height/2
            )
    );

    // Create a menu with the "close" menu item, it's an auto release object.
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    if (!pMenu)
        return false;

    // Add the menu to GameplayScene layer as a child layer.
}

void GameplayScene::menuCloseCallback(CCObject* pSender)
{
	// "close" menu item clicked
	CCDirector::sharedDirector()->end();
}


/*
void GameplayScene::ccTouchesMoved(CCSet* touches, CCEvent* event)
{
    CCTouch *touch = (CCTouch*)touches->anyObject();
    CCPoint diff = touch->getDelta();
    
    CCNode* node = getChildByTag(7);
    CCPoint currentPos = node->getPosition();
    node->setPosition( ccpAdd(currentPos, diff) );
}
*/

// cpp with cocos2d-x
void GameplayScene::ccTouchesEnded(CCSet* touches, CCEvent* event)
{
	//CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("pew-pew-lei.wav");
}


void GameplayScene::registerWithTouchDispatcher()
{
	// CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this,0,true);
    CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate(this,0);
}
