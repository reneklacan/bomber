#include "GameplayScene.h"
#include "GameOverScene.h"
//#include "SimpleAudioEngine.h"

using namespace cocos2d;

GameplayScene::~GameplayScene()
{
}

GameplayScene::GameplayScene()
:_levelLayer(NULL)
{
}

Scene* GameplayScene::scene()
{
	Scene * scene = NULL;
    // 'scene' is an autorelease object
    scene = Scene::create();
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

    return true;
}

void GameplayScene::menuCloseCallback(Object* pSender)
{
	// "close" menu item clicked
	Director::sharedDirector()->end();
}


/*
void GameplayScene::ccTouchesMoved(Set* touches, Event* event)
{
    Touch *touch = (Touch*)touches->anyObject();
    Point diff = touch->getDelta();
    
    CCNode* node = getChildByTag(7);
    Point currentPos = node->getPosition();
    node->setPosition( ccpAdd(currentPos, diff) );
}
*/

// cpp with cocos2d-x
void GameplayScene::ccTouchesEnded(Set* touches, Event* event)
{
	//CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("pew-pew-lei.wav");
}


void GameplayScene::registerWithTouchDispatcher()
{
	// TouchDispatcher::sharedDispatcher()->addTargetedDelegate(this,0,true);
    Director::sharedDirector()->getTouchDispatcher()->addStandardDelegate(this,0);
}
