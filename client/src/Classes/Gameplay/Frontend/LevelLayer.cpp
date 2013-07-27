#include "LevelLayer.h"
#include "../../Constants.h"
#include "../Backend/Mediator.h"
#include "../Backend/GameObjects/Sprites/Bomber.h"
#include "Buttons/GameButton.h"
#include "GUIUpdater.h"
#include "ButtonLayer.h"
#include "Buttons/ControlButton.h"

using namespace Bomber;
using namespace Bomber::Frontend;

LevelLayer::LevelLayer()
:_player1(NULL)
,_player2(NULL)
,_map(NULL)
,_gamePaused(false)
,_lastChangeID(0)
,_controlledSprite(NULL)
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
    
    _player1 = Human::create(_map, 0);
    _player1->setID(19991);
    _player2 = Human::create(_map, 0);
    _player2->setID(19992);

    _controlLayer = ControlLayer::create();

    this->addChild(_map);
    this->addChild(_controlLayer, 2);

    // Frontend init
    GUIUpdater::getInstance()->init(_map, _player1, _player2, this);

    // Game State init
    _gameState = new Common::GameState(_map->getWidth(), _map->getHeight());
    Backend::Mediator::getInstance()->setState(_gameState);
    _gameState->init(_map->getTiledMap());
    
    // Backend init
    this->initControlledSprite();

    // Button Layer
    ButtonLayer::getInstance()->setMainLayer(this);
    /**
    */

    // Quit Button
    ControlButton *cbQuit = new ControlButton(
        0,
        "buttons/button_black_power_64.png",
        this,
        menu_selector(LevelLayer::menuCloseCallback)
    );
    ButtonLayer::getInstance()->addToControls(cbQuit);

    // Pause/Resume Button
    ControlButton *cbPause = new ControlButton(
        0,
        "buttons/button_black_pause_64.png",
        this,
        menu_selector(LevelLayer::menuPauseCallback)
    );
    ButtonLayer::getInstance()->addToControls(cbPause);

    // Reset Button
    ControlButton *cbReset = new ControlButton(
        0,
        "buttons/button_black_repeat_64.png",
        this,
        menu_selector(LevelLayer::menuResetCallback)
    );
    ButtonLayer::getInstance()->addToControls(cbReset);

    /**
    */

    // Control Layer
    this->initControlLayer();
    
    // Backend init
    Backend::Mediator::getInstance()->moveSprite(
            Common::Position(
                _player1->getPosition().x,
                _player1->getPosition().y
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
    // player 1

    // Get all information
    Point currentPos = _player1->getPosition();
    Point nextPos = _player1->getNextPosition();
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
        _player1->setPosition(nextPos);
        _map->addToPosition(ccpSub(currentPos, nextPos));
        Backend::Mediator::getInstance()->moveSprite(Common::Position(nextPos.x, nextPos.y));
    }

    // player 2

    // Get all information
    currentPos = _player2->getPosition();
    nextPos = _player2->getNextPosition();
    nextPosX = ccp(nextPos.x, currentPos.y);
    nextPosY = ccp(currentPos.x, nextPos.y);

    // Count collisions
    collisions.clear();
    collisions = GUIUpdater::getInstance()->evalCollisions(currentPos, nextPos);

    // Set whether player has moved
    move = true;
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
        _player2->setPosition(nextPos);
        // TODO: move with id on the backend, both of players
        //Backend::Mediator::getInstance()->moveSprite(Common::Position(nextPos.x, nextPos.y));
    }

    // Send action
    Backend::Mediator::getInstance()->update(dt);

    // Draw new state
    GUIUpdater::getInstance()->update();
    ButtonLayer::getInstance()->saveTime(dt);

    // Reset level if needed
    if( GUIUpdater::getInstance()->isResetSet() )
    {
        this->resetLevel();
    }
    
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
    this->resetLevel();
}

//
void LevelLayer::resetLevel()
{
    // "reset" menu item clicked
    GUIUpdater::getInstance()->resetGUI();
    Backend::Mediator::getInstance()->resetState();

    // Backend init
    this->initControlledSprite();
}

//
void LevelLayer::initControlledSprite()
{
    // spawnpoint is calculated on backend
    _controlledSprite = Backend::Mediator::getInstance()->getControlledSprite();
    _player1->setPosition(
        ccp(
            _controlledSprite->getPosition().x,
            _controlledSprite->getPosition().y
        )
    );
    _player1->setNextPosition(_player1->getPosition());
    _player1->setSpeed(_controlledSprite->getAttributes()->getSpeed());

    // set view that timmy is in the center of it
    Size visibleSize = Director::sharedDirector()->getVisibleSize();
    _map->setPosition(
        ccp(
            visibleSize.width/2 - _player1->getPosition().x,
            visibleSize.height/2 - _player1->getPosition().y
        )
    );

    // player 2
    _player2->setPosition(
        ccp(
            _controlledSprite->getPosition().x,
            _controlledSprite->getPosition().y
        )
    );
    _player2->setNextPosition(_player2->getPosition());
    _player2->setSpeed(_controlledSprite->getAttributes()->getSpeed());
}

//
void LevelLayer::initControlLayer()
{
    _controlLayer->enableJoystick();
    _controlLayer->enableKeyboard();
    _controlLayer->setPauseGameDelegate(this);
    _controlLayer->setControlledPlayer1(_player1);
    _controlLayer->setControlledPlayer2(_player2);
}
