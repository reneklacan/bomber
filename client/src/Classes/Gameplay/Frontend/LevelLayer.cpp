#include "LevelLayer.h"
#include "../../Constants.h"
#include "../Backend/Mediator.h"
#include "../Backend/Bomber.h"
#include "GameButton.h"
#include "GUIUpdater.h"
#include "ButtonLayer.h"
#include "ControlButton.h"

using namespace Bomber;
using namespace Bomber::Frontend;

LevelLayer::LevelLayer()
:_player(NULL)
,_map(NULL)
,_gamePaused(false)
,_lastChangeID(0)
{
}

LevelLayer::~LevelLayer()
{
}

bool LevelLayer::init()
{
    Director::sharedDirector()->setDepthTest(true);
    Director::sharedDirector()->setProjection(kDirectorProjection2D);

    if (!Layer::init())
        return false;

    _map = Map::create();
    _player = Human::create(_map);
    _controlLayer = ControlLayer::create();

    Backend::GameState *gameState = new Backend::GameState(_map->getWidth(), _map->getHeight());
    Backend::Mediator::getInstance()->setState(gameState);
    gameState->init(_map->getTiledMap());
    
    Backend::Bomber *controlledSprite = new Backend::Bomber();
    controlledSprite->setId(19991);
    controlledSprite->setPosition(_player->getPosition().x, _player->getPosition().y);
    controlledSprite->setSize(10, 10);
    gameState->getSpriteLayer()->addObject(controlledSprite);

    _player->setID(19991);

    Backend::Mediator::getInstance()->setControlledSprite(controlledSprite->getId());
    GUIUpdater::getInstance()->init(_map, _player, this);

    _player->retain();

    this->addChild(_map);
    this->addChild(_controlLayer, 2);

    /**
    */

    // Quit Button
    ControlButton *cbQuit = new ControlButton(
        0,
        "CloseNormal.png",
        this,
        menu_selector(LevelLayer::menuCloseCallback)
    );
    ButtonLayer::getInstance()->addToControls(cbQuit);
    this->addChild(cbQuit->getGameButton(), 1);

    // Pause/Resume Button
    ControlButton *cbPause = new ControlButton(
        0,
        "CloseNormal.png",
        this,
        menu_selector(LevelLayer::menuPauseCallback)
    );
    ButtonLayer::getInstance()->addToControls(cbPause);
    this->addChild(cbPause->getGameButton(), 1);
    /**
    */

    _map->addChild(_player, 1);

    Size visibleSize = Director::sharedDirector()->getVisibleSize();
    Point origin = Director::sharedDirector()->getVisibleOrigin();
    
    //_player = (GameSprite *) layer->tileAt(ccp(0, 5));
    //_player = GameSprite::gameSpriteWithFile("tiles/timmy.png");
    //_player->setSpeed(1);
    //_player->setPosition(CC_POINT_PIXELS_TO_POINTS(ccp(mapWidth/2,0)));
    _player->setAnchorPoint(ccp(0.5f, 0.0f));

    _controlLayer->setControlledSprite((GameSprite *)_player);
    _controlLayer->enableJoystick();
    _controlLayer->enableKeyboard();
    _controlLayer->setPauseGameDelegate(this);
    _controlLayer->setGameActionDelegate(_player);
    
    _player->setPosition(
            ccp(
                origin.x + _player->getContentSize().width/2 + 101,
                origin.y + visibleSize.height/2
            )
    );
    _player->setNextPosition(_player->getPosition());

    Backend::Mediator::getInstance()->moveSprite(
            Position(
                _player->getPosition().x,
                _player->getPosition().y
            )
    );

    _map->setPosition(
            ccp(
                visibleSize.width/2 - _player->getPosition().x,
                0
            )
    );

    // use updateGame instead of update, otherwise it will conflit with SelectorProtocol::update
    // see http://www.cocos2d-x.org/boards/6/topics/1478
    this->schedule( schedule_selector(LevelLayer::repositionSprite) );
    this->schedule( schedule_selector(LevelLayer::updateGame) );

    //CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("background-music-aac.wav", true);

    return true;
}

void LevelLayer::repositionSprite(float dt)
{
    Point p = _player->getPosition();
    //p = CC_POINT_POINTS_TO_PIXELS(p);
    int z = -( (p.y+100.5) /81 ) + 0;
    _player->setVertexZ( z );
}

void LevelLayer::updateGame(float dt)
{
    Rect objRect;
    bool collisionOccured = false;
    bool collisionOccuredX = false;
    bool collisionOccuredY = false;

    Point currentPos = _player->getPosition();
    Point nextPos = _player->getNextPosition();
    Point nextPosX = ccp(nextPos.x, currentPos.y);
    Point nextPosY = ccp(currentPos.x, nextPos.y);

    Rect playerRect = _player->getCollisionBox();
    Rect playerRectX = _player->getCollisionBox(nextPosX);
    Rect playerRectY = _player->getCollisionBox(nextPosY);

    TMXLayer *obstaclesLayer = _map->getTiledMap()->layerNamed("obstacles");

    Point tilemapPosition = _player->getTilemapPosition();

    for (int iy = tilemapPosition.y - 1; iy <= tilemapPosition.y + 1; iy++)
    {
        for (int ix = tilemapPosition.x - 1; ix <= tilemapPosition.x + 1; ix++)
        {
            if (!obstaclesLayer->tileGIDAt(ccp(ix, _map->getHeight() - 1 - iy)))
                continue;

            objRect = CCRectMake(ix*TILE_WIDTH, iy*TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT);

            if (!collisionOccured && playerRect.intersectsRect(objRect))
                collisionOccured = true;
            if (!collisionOccuredX && playerRectX.intersectsRect(objRect))
                collisionOccuredX = true;
            if (!collisionOccuredY && playerRectY.intersectsRect(objRect))
                collisionOccuredY = true;
        }
    }

    bool move = true;

    if (!collisionOccured)
        ;
    else if (!collisionOccuredX)
        nextPos = nextPosX;
    else if (!collisionOccuredY)
        nextPos = nextPosY;
    else
        move = false;

    if (move && (currentPos.x != nextPos.x || currentPos.y != nextPos.y))
    {
        _player->setPosition(nextPos);
        _map->addToPosition(ccpSub(currentPos, nextPos));
        Backend::Mediator::getInstance()->moveSprite(Position(nextPos.x, nextPos.y));
    }

    Backend::Mediator::getInstance()->update(dt);

    // Draw new state
    GUIUpdater::getInstance()->update(currentPos);
    //this->updateFromGameState(currentPos);
    
}

//
void LevelLayer::menuCloseCallback(Object* pSender)
{
    // "close" menu item clicked
    Director::sharedDirector()->end();
}

//
void LevelLayer::menuPauseCallback(Object* pSender)
{
    // "pause/resume" menu item clicked
    if(_gamePaused)
    {
        Director::sharedDirector()->resume();
        _gamePaused = false;
    }
    else
    {
        Director::sharedDirector()->pause();
        _gamePaused = true;
    }
}
