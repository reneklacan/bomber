#include "LevelLayer.h"
#include "../../Constants.h"
#include "../Backend/Mediator.h"
#include "../Backend/Bomber.h"
#include "Buttons/GameButton.h"
#include "GUIUpdater.h"
#include "ButtonLayer.h"
#include "Buttons/ControlButton.h"

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

    // Basic init
    _map = Map::create();
    _player = Human::create(_map, 0);
    _controlLayer = ControlLayer::create();
    this->addChild(_map);
    this->addChild(_controlLayer, 2);

    // Frontend init
    GUIUpdater::getInstance()->init(_map, _player, this);

    // Game State init
    Backend::GameState *gameState = new Backend::GameState(_map->getWidth(), _map->getHeight());
    Backend::Mediator::getInstance()->setState(gameState);
    gameState->init(_map->getTiledMap());
    
    // Backend init
    Backend::Bomber *controlledSprite = new Backend::Bomber();
    controlledSprite->setId(19991);
    controlledSprite->setPosition(_player->getPosition().x, _player->getPosition().y);
    controlledSprite->setSize(10, 10);
    gameState->getSpriteLayer()->addObject(controlledSprite);

    _player->setID(19991);

    Backend::Mediator::getInstance()->setControlledSprite(controlledSprite->getId());

    // Button Layer
    ButtonLayer::getInstance()->setMainLayer(this);
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

    // Pause/Resume Button
    ControlButton *cbPause = new ControlButton(
        0,
        "CloseNormal.png",
        this,
        menu_selector(LevelLayer::menuPauseCallback)
    );
    ButtonLayer::getInstance()->addToControls(cbPause);

    // Reset Button
    ControlButton *cbReset = new ControlButton(
        0,
        "CloseNormal.png",
        this,
        menu_selector(LevelLayer::menuResetCallback)
    );
    ButtonLayer::getInstance()->addToControls(cbReset);

    /**
    */

    // Control Layer
    _controlLayer->setControlledSprite((GameSprite *)_player);
    _controlLayer->enableJoystick();
    _controlLayer->enableKeyboard();
    _controlLayer->setPauseGameDelegate(this);
    _controlLayer->setGameActionDelegate(_player);
    
    // Backend init
    Backend::Mediator::getInstance()->moveSprite(
            Position(
                _player->getPosition().x,
                _player->getPosition().y
            )
    );


    // use updateGame instead of update, otherwise it will conflit with SelectorProtocol::update
    // see http://www.cocos2d-x.org/boards/6/topics/1478
    this->schedule( schedule_selector(LevelLayer::updateGame) );

    //CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("background-music-aac.wav", true);

    return true;
}

void LevelLayer::updateGame(float dt)
{
    // Get all information
    Point currentPos = _player->getPosition();
    Point nextPos = _player->getNextPosition();
    Point nextPosX = ccp(nextPos.x, currentPos.y);
    Point nextPosY = ccp(currentPos.x, nextPos.y);

    // Count collisions
    std::vector<bool> collisions;
    collisions = GUIUpdater::getInstance()->evalCollisions(currentPos, nextPos);

    // Set whether player has moved
    bool move = true;
    if (!collisions[0])
        ;
    else if (!collisions[1])
        nextPos = nextPosX;
    else if (!collisions[2])
        nextPos = nextPosY;
    else
        move = false;

    // Move player without backend
    if (move && (currentPos.x != nextPos.x || currentPos.y != nextPos.y))
    {
        _player->setPosition(nextPos);
        _map->addToPosition(ccpSub(currentPos, nextPos));
        Backend::Mediator::getInstance()->moveSprite(Position(nextPos.x, nextPos.y));
    }

    // Send action
    Backend::Mediator::getInstance()->update(dt);

    // Draw new state
    GUIUpdater::getInstance()->update(currentPos);
    ButtonLayer::getInstance()->saveTime(dt);
    
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

//
void LevelLayer::menuResetCallback(Object* pSender)
{
    // "reset" menu item clicked
    Backend::Mediator::getInstance()->resetState();
}
