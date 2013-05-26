#include "GameplayScene.h"
#include "GameOverScene.h"
#include "SimpleAudioEngine.h"
#include "Joystick.h"

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
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(! CCLayerColor::initWithColor( ccc4(255,255,255,255) ) );

        _map = CCTMXTiledMap::create("tiles/tilemap.tmx");
        this->addChild(_map, 0, 7);
        _map->setPosition(ccp(0,0));
        CCSize CC_UNUSED s = _map->getContentSize();
        CCLog("ContentSize: %f, %f", s.width,s.height);

        Joystick *joystick =  Joystick::create();
        this->addChild(joystick,2);
        this->setJoystick(joystick);

		// Create a "close" menu item with close icon, it's an auto release object.
		CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                "CloseNormal.png",
                "CloseSelected.png",
                this,
                menu_selector(GameplayScene::menuCloseCallback)
        );
		CC_BREAK_IF(! pCloseItem);
        
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
		CC_BREAK_IF(! pMenu);

		// Add the menu to GameplayScene layer as a child layer.
		this->addChild(pMenu, 1);

        CCTMXLayer* layer = _map->layerNamed("players");
        _player = layer->tileAt(ccp(0, 5));
        _player->retain();
        //_player->setPosition(CC_POINT_PIXELS_TO_POINTS(ccp(mapWidth/2,0)));
        _player->setAnchorPoint(ccp(0.5f, 0.3f));

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

		_targets = new CCArray;
		_projectiles = new CCArray;

		// use updateGame instead of update, otherwise it will conflit with SelectorProtocol::update
		// see http://www.cocos2d-x.org/boards/6/topics/1478
		this->schedule( schedule_selector(GameplayScene::updateGame) );

		//CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("background-music-aac.wav", true);

		bRet = true;
	} while (0);

	return bRet;
}

void GameplayScene::menuCloseCallback(CCObject* pSender)
{
	// "close" menu item clicked
	CCDirector::sharedDirector()->end();
}

// cpp with cocos2d-x
void GameplayScene::addTarget()
{
	CCSprite *target = CCSprite::create("Target.png", CCRectMake(0,0,27,40) );
    
	// Determine where to spawn the target along the Y axis
	CCSize winSize = CCDirector::sharedDirector()->getVisibleSize();
	float minY = target->getContentSize().height/2;
	float maxY = winSize.height -  target->getContentSize().height/2;
	int rangeY = (int)(maxY - minY);
	// srand( TimGetTicks() );
	int actualY = ( rand() % rangeY ) + (int)minY;

	// Create the target slightly off-screen along the right edge,
	// and along a random position along the Y axis as calculated
	target->setPosition( 
            ccp(
                winSize.width + (target->getContentSize().width/2), 
                CCDirector::sharedDirector()->getVisibleOrigin().y + actualY
            )
    );
	this->addChild(target);

	// Determine speed of the target
	int minDuration = (int)150.0;
	int maxDuration = (int)170.0;
	int rangeDuration = maxDuration - minDuration;
	// srand( TimGetTicks() );
	int actualDuration = ( rand() % rangeDuration ) + minDuration;

	// Create the actions
	CCFiniteTimeAction* actionMove = CCMoveTo::create(
            (float)actualDuration,
            ccp(0 - target->getContentSize().width/2, actualY)
    );
	CCFiniteTimeAction* actionMoveDone = CCCallFuncN::create(
            this, 
            callfuncN_selector(GameplayScene::spriteMoveFinished)
    );
	target->runAction( CCSequence::create(actionMove, actionMoveDone, NULL) );

	// Add to targets array
	target->setTag(1);
	_targets->addObject(target);
}

void GameplayScene::spriteMoveFinished(CCNode* sender)
{
	CCSprite *sprite = (CCSprite *)sender;
	this->removeChild(sprite, true);

	if (sprite->getTag() == 1)  // target
	{
		_targets->removeObject(sprite);
        
		GameOverScene *gameOverScene = GameOverScene::create();
		gameOverScene->getLayer()->getLabel()->setString("You Lose :[");
		CCDirector::sharedDirector()->replaceScene(gameOverScene);

	}
	else if (sprite->getTag() == 2) // projectile
	{
		_projectiles->removeObject(sprite);
	}
}

void GameplayScene::gameLogic(float dt)
{
	this->addTarget();
}

// cpp with cocos2d-x
void GameplayScene::ccTouchesEnded(CCSet* touches, CCEvent* event)
{
    CCPoint origin = _player->getPosition();

    /*
	// Choose one of the touches to work with
	CCTouch* touch = (CCTouch*)( touches->anyObject() );
	CCPoint location = touch->getLocation();
    
	CCLog("++++++++after  x:%f, y:%f", location.x, location.y);

	// Set up initial location of projectile
	CCSize winSize = CCDirector::sharedDirector()->getVisibleSize();
    //CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	CCSprite *projectile = CCSprite::create("Projectile.png", CCRectMake(0, 0, 20, 20));
	projectile->setPosition(origin);

	// Determinie offset of location to projectile
	float offX = location.x - projectile->getPosition().x;
	float offY = location.y - projectile->getPosition().y;

	// Ok to add now - we've double checked position
	this->addChild(projectile);

	// Determine where we wish to shoot the projectile to
    float realX = origin.x;
    float realY = origin.y;

    while (realX > 0 && realX < winSize.width && realY > 0 && realY < winSize.height)
    {
        realX += offX;
        realY += offY;
    }

    CCPoint realDest;

    realDest = ccp(realX, realY);

	// Determine the length of how far we're shooting
	float offRealX = realX - projectile->getPosition().x;
	float offRealY = realY - projectile->getPosition().y;
	float length = sqrtf((offRealX * offRealX) + (offRealY*offRealY));
	float velocity = 480/1; // 480pixels/1sec
	float realMoveDuration = length/velocity;

	// Move projectile to actual endpoint
	projectile->runAction(
            CCSequence::create(
                CCMoveTo::create(realMoveDuration, realDest),
                CCCallFuncN::create(
                    this, 
                    callfuncN_selector(GameplayScene::spriteMoveFinished)
                ), 
                NULL
            )
    );

	// Add to projectiles array
	projectile->setTag(2);
	_projectiles->addObject(projectile);

	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("pew-pew-lei.wav");
    */

    ////////////////////////////

    //CCParticleSmoke *emitter = CCParticleSmoke::create();
    
    // one for each direction
    for (int i = 0; i < 4; i++)
    {
        CCParticleFire *emitter = CCParticleFire::create();
        emitter->retain();
        this->addChild(emitter, 10);
        emitter->setTexture(CCTextureCache::sharedTextureCache()->addImage("particles/fire.png"));
        emitter->initWithTotalParticles(500);
        emitter->setStartSize(100.0f);
        emitter->setLife(2);
        emitter->setLifeVar(1);
        //emitter->setSpeed(60);
        //emitter->setSpeedVar(20);
        emitter->setDuration(0.5);
        emitter->setPosition(origin);
        CCActionInterval* move;

        if (i == 0)
        {
            emitter->setAngle(0);
            move = CCMoveBy::create(2, ccp(500, 0));
        }
        else if (i == 1)
        {
            emitter->setAngle(90);
            move = CCMoveBy::create(2, ccp(0, 200));
        }
        else if (i == 2)
        {
            emitter->setAngle(180);
            move = CCMoveBy::create(2, ccp(-500, 0));
        }
        else if (i == 3)
        {
            emitter->setAngle(-90);
            move = CCMoveBy::create(2, ccp(0, -500));
        }
        emitter->setAngleVar(0);
        emitter->setAutoRemoveOnFinish(true);
        //CCActionInterval* move_back = CCHide::create();
        CCSequence* seq = CCSequence::create(move, NULL);
        emitter->runAction(CCSpeed::create(seq, 5));
    }
}

void GameplayScene::updateGame(float dt)
{
	CCArray *projectilesToDelete = new CCArray;
    CCObject* it = NULL;
    CCObject* jt = NULL;
    CCObject* co = NULL;

    CCPoint pos = _player->getPosition();
    _player->setPosition(
            ccp(
                pos.x + _joystick->getVelocity().x*_sensitivity,
                pos.y + _joystick->getVelocity().y*_sensitivity
            )
    );

    CCRect playerRect = CCRectMake(
            _player->getPosition().x - (_player->getContentSize().width/4),
            _player->getPosition().y - (_player->getContentSize().height/4),
            _player->getContentSize().width/2,
            _player->getContentSize().height/2
    );

    CCTMXObjectGroup *objectGroup = _map->objectGroupNamed("collx");
    CCArray *objectList = objectGroup->getObjects();

    CCDictionary *dict;
    int x, y, width, height;
    CCRect objRect;

    CCARRAY_FOREACH(objectList, co)
    {
        dict = (CCDictionary*)co;

        if(!dict)
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
            _player->setPosition(pos);

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

            break;
        }

    }

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
