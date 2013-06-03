#include "GameplayScene.h"
#include "GameOverScene.h"
#include "SimpleAudioEngine.h"
#include "Input/Joystick.h"
#include "Input/Keyboard.h"
#include "Input/ControlLayer.h"
#include "Gameplay/Map/Bomb.h"

using namespace cocos2d;

GameplayScene::~GameplayScene()
{
	if (_targets)
	{
		_targets->release();
		_targets = NULL;
	}

	if (_projectiles)
	{
		_projectiles->release();
		_projectiles = NULL;
	}

	// cpp don't need to call super dealloc
	// virtual destructor will do this
}

GameplayScene::GameplayScene()
:_targets(NULL)
,_projectiles(NULL)
,_projectilesDestroyed(0)
,_sensitivity(5)
{
}

CCScene* GameplayScene::scene()
{
	CCScene * scene = NULL;
	do 
	{
		// 'scene' is an autorelease object
		scene = CCScene::create();
		CC_BREAK_IF(! scene);

		// 'layer' is an autorelease object
		GameplayScene *layer = GameplayScene::create();
		CC_BREAK_IF(! layer);
;
		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool GameplayScene::init()
{
    CCDirector::sharedDirector()->setDepthTest(true);
    CCDirector::sharedDirector()->setProjection(kCCDirectorProjection2D);

    if (!CCLayer::init())
        return false;

    _keyboard = CCDirector::sharedDirector()->getKeyboardDispatcher();
    //CCNode *root = new CCNode();

    _tileMap = CCTMXTiledMap::create("tiles/tilemap.tmx");
    _map = new Map();
    this->addChild(_map);
    _map->addChild(_tileMap, 0, 7);
    CCSize CC_UNUSED s = _tileMap->getContentSize();
    CCLog("ContentSize: %f, %f", s.width,s.height);

    ControlLayer* controlLayer = ControlLayer::create();
    //Joystick *joystick =  Joystick::create();
    this->addChild(controlLayer, 2);
    //this->setJoystick(joystick);

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
    this->addChild(pMenu, 1);

    //CCTMXLayer* layer = _tileMap->layerNamed("trees");
    //_player = (GameSprite *) layer->tileAt(ccp(0, 5));
    //_player = GameSprite::gameSpriteWithFile("tiles/timmy.png");
    _player = Human::create(_map);
    _map->addChild(_player, 1);
    //_player->setSpeed(1);
    _player->retain();
    //_player->setPosition(CC_POINT_PIXELS_TO_POINTS(ccp(mapWidth/2,0)));
    //_player->setAnchorPoint(ccp(0.5f, 0.3f));
    controlLayer->setControlledSprite((GameSprite *)_player);
    //controlLayer->enableJoystick();
    controlLayer->enableKeyboard();

    //CCPoint playerPos = _player->getPosition();

    _tileMap->setPosition( ccp(0, 0) );

    CCLog(
            "++++++++Player width:%f, height:%f",
            _player->getContentSize().width,
            _player->getContentSize().height
    );
    CCLog(
            "++++++++Player x:%f, y:%f",
            _player->getPosition().x,
            _player->getPosition().y
    );
    
    _player->setPosition(
            ccp(
                origin.x + _player->getContentSize().width/2,
                origin.y + visibleSize.height/2
            )
    );
    //this->addChild(_player);

    //this->schedule( schedule_selector(GameplayScene::gameLogic), 1.0 );

    this->setTouchEnabled(true);
    //this->setKeyboardEnabled(true);

    _targets = new CCArray;
    _projectiles = new CCArray;

    // use updateGame instead of update, otherwise it will conflit with SelectorProtocol::update
    // see http://www.cocos2d-x.org/boards/6/topics/1478
    this->schedule( schedule_selector(GameplayScene::repositionSprite) );
    this->schedule( schedule_selector(GameplayScene::updateGame) );

    //CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("background-music-aac.wav", true);

	return true;
}

void GameplayScene::repositionSprite(float dt)
{
    CCPoint p = _player->getPosition();
    //p = CC_POINT_POINTS_TO_PIXELS(p);
    int z = -( (p.y+100.5) /81 ) + 0;
    _player->setVertexZ( z );
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

void GameplayScene::updateGame(float dt)
{
	CCArray *projectilesToDelete = new CCArray;
    CCObject* it = NULL;
    CCObject* jt = NULL;
    CCObject* co = NULL;

    CCPoint nextPos = _player->getNextPosition();

    CCRect playerRect = CCRectMake(
            nextPos.x - (_player->getContentSize().width/4),
            nextPos.y - (_player->getContentSize().height/4),
            _player->getContentSize().width/2,
            _player->getContentSize().height/2
    );

    CCTMXObjectGroup *objectGroup = _tileMap->objectGroupNamed("colliders");
    CCArray *objectList = objectGroup->getObjects();

    CCDictionary *dict;
    int x, y, width, height;
    CCRect objRect;

    bool collisionOccured = false;

    CCARRAY_FOREACH(objectList, co)
    {
        dict = (CCDictionary*)co;

        if (!dict)
            break;

        x = ((CCString*)dict->objectForKey("x"))->intValue();
        y = ((CCString*)dict->objectForKey("y"))->intValue();
        width = ((CCString*)dict->objectForKey("width"))->intValue();
        height = ((CCString*)dict->objectForKey("height"))->intValue();         

        //printf( "x %i, y %i, width %i, height %i\n", x, y, width, height );

        objRect = CCRectMake(
                x, y, width, height
        );
        //printf("obj rect height is %g\n", objRect.size.height);

        if (playerRect.intersectsRect(objRect))
        {
            std::cout << "collision" << std::endl;
            //_player->setPosition(pos);

            CCLog(
                    "++++++++Player width:%f, height:%f",
                    playerRect.size.width,
                    playerRect.size.height
            );
            CCLog(
                    "++++++++Player x:%f, y:%f",
                    playerRect.origin.x,
                    playerRect.origin.y
            );

            CCLog(
                    "++++++++obj width:%f, height:%f",
                    objRect.size.width,
                    objRect.size.height
            );
            CCLog(
                    "++++++++obj x:%f, y:%f",
                    objRect.origin.x,
                    objRect.origin.y
            );

            collisionOccured = true;

            break;
        }

    }

    if (!collisionOccured)
    {
        _player->setPosition(nextPos);
    }

    if (!collisionOccured)
    {
        CCPoint mapPos = _map->getPosition();
        _map->setPosition(
                ccpAdd(mapPos, ccpNeg(_player->getNextPositionDelta()))
        );
    }
    //tree = layer->tileAt(ccp(1, 6));
    //std::cout << "tree vz: " << tree->getVertexZ() << std::endl;

    //CCPoint playerPos = _player->getPosition();
    //int coordX = ((int) (playerPos.x - _player->getContentSize().width/2 + 40.5f)/81);
    //int coordY = ((int) (playerPos.y - _player->getContentSize().height/2 + 50.5f)/101);
    //coordX = (int) (playerPos.x - _player->getContentSize().width/2 + 35.5f)/101;
    //coordY = (int) (playerPos.y - _player->getContentSize().height/2 + 55.5f)/81;

    //CCLog("player pos   : x:%f, y:%f", playerPos.x, playerPos.y);
    //CCLog(
    //        "player pos2  : x:%f, y:%f",
    //        playerPos.x - _player->getContentSize().width/2,
    //        playerPos.y - _player->getContentSize().height/2
    //);
    //CCLog(
    //        "player pos3  : x:%d, y:%d",
    //        (int) (playerPos.x - _player->getContentSize().width/2 + 40.5f + 10.0f)/101,
    //        (int) (playerPos.y - _player->getContentSize().height/2 + 50.5f - 19.0f)/81
    //);
    //CCLog("player coords: x:%d, y:%d", coordX, coordY);

	// for (it = _projectiles->begin(); it != _projectiles->end(); it++)
    CCARRAY_FOREACH(_projectiles, it)
	{
		CCSprite *projectile = dynamic_cast<CCSprite*>(it);
		CCRect projectileRect = CCRectMake(
                projectile->getPosition().x - (projectile->getContentSize().width/2),
                projectile->getPosition().y - (projectile->getContentSize().height/2),
                projectile->getContentSize().width,
                projectile->getContentSize().height
        );

		CCArray* targetsToDelete = new CCArray;

		// for (jt = _targets->begin(); jt != _targets->end(); jt++)
        CCARRAY_FOREACH(_targets, jt)
		{
			CCSprite *target = dynamic_cast<CCSprite*>(jt);
			CCRect targetRect = CCRectMake(
                    target->getPosition().x - (target->getContentSize().width/2),
                    target->getPosition().y - (target->getContentSize().height/2),
                    target->getContentSize().width,
                    target->getContentSize().height
            );

			// if (CCRect::CCRectIntersectsRect(projectileRect, targetRect))
            if (projectileRect.intersectsRect(targetRect))
			{
				targetsToDelete->addObject(target);
			}
		}

		// for (jt = targetsToDelete->begin(); jt != targetsToDelete->end(); jt++)
        CCARRAY_FOREACH(targetsToDelete, jt)
		{
			CCSprite *target = dynamic_cast<CCSprite*>(jt);
			_targets->removeObject(target);
			this->removeChild(target, true);

			_projectilesDestroyed++;
			if (_projectilesDestroyed >= 15)
			{
				GameOverScene *gameOverScene = GameOverScene::create();
				gameOverScene->getLayer()->getLabel()->setString("You Win!");
				CCDirector::sharedDirector()->replaceScene(gameOverScene);
			}
		}

		if (targetsToDelete->count() > 0)
		{
			projectilesToDelete->addObject(projectile);
		}
		targetsToDelete->release();
	}

	// for (it = projectilesToDelete->begin(); it != projectilesToDelete->end(); it++)
    CCARRAY_FOREACH(projectilesToDelete, it)
	{
		CCSprite* projectile = dynamic_cast<CCSprite*>(it);
		_projectiles->removeObject(projectile);
		this->removeChild(projectile, true);
	}
	projectilesToDelete->release();
}

void GameplayScene::registerWithTouchDispatcher()
{
	// CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this,0,true);
    CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate(this,0);
}

void GameplayScene::setJoystick(Joystick *joystick)
{
    _joystick = joystick;
}
