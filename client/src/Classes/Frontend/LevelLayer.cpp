#include "LevelLayer.h"
#include "../Constants.h"
#include "../Common/Storage/XMLStorage.h"
#include "../Backend/Mediator.h"
#include "../Backend/GameObjects/Sprites/Bomber.h"
#include "Buttons/GameButton.h"
#include "ButtonLayer.h"
#include "Buttons/ControlButton.h"
#include "Primitives/MenuHelper.h"
#include "../Menu/LevelSelectLayer.h"
#include "../Menu/MainMenuLayer.h"

using namespace Bomber;
using namespace Bomber::Frontend;

LevelLayer::LevelLayer()
:_player1(NULL)
,_player2(NULL)
,_map(NULL)
,_gamePaused(false)
,_lastChangeID(0)
{
    _players.clear();
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
    _gui = new GUIUpdater();
    _map = Map::create();

    // Init Mediator according to connection type
    Backend::Mediator::getInstance()->setConnectionType( MenuSelections::getInstance()->getConnection() );
    
    // Player init
    unsigned int playerID = 19990;
    for(int i = 0; i < MenuSelections::getInstance()->getNumPlayers(); i++)
    {
        playerID++;
        _players[playerID] = Human::create(_map, 0);
        _players[playerID]->setID(playerID);
    }
    /*_player1 = Human::create(_map, 0);
    _player1->setID(19991);
    _player2 = Human::create(_map, 0);
    _player2->setID(19992);*/

    _controlLayer = ControlLayer::create();

    this->addChild(_map);
    this->addChild(_controlLayer, 2);

    // Frontend init
    _gui->init(_map, _players, this);

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
        _players[19991]->getID(),
        Common::Position(
            _players[19991]->getPosition().x,
            _players[19991]->getPosition().y
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
    //
    if(_gamePaused)
    {
        return;
    }

    // Count collisions
    std::vector<bool> collisions;
    for(auto playerData : _players)
    {
        Human *player = playerData.second;

        // Eval only linig players
        if( !_gui->isPlayerAlive( player->getID() ) )
        {
            continue;
        }

        // Get all information
        Point currentPos = player->getPosition();
        Point nextPos = player->getNextPosition();
        Point nextPosX = ccp(nextPos.x, currentPos.y);
        Point nextPosY = ccp(currentPos.x, nextPos.y);

        // Clear
        collisions.clear();
        collisions = _gui->evalCollisions(player);

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
            // Player
            player->setPosition(nextPos);
            // Map
            if(player->getID() == 19991) // WARNING
            {
                _map->addToPosition(ccpSub(currentPos, nextPos));
            }
            // Backend
            Backend::Mediator::getInstance()->moveSprite(
                player->getID(),
                Common::Position(nextPos.x, nextPos.y)
            );
        }
    }

    // Send action
    Backend::Mediator::getInstance()->update(dt);

    // Draw new state
    _gui->update();
    ButtonLayer::getInstance()->saveTime(dt);

    // Reset level if needed
    if( _gui->isResetSet() )
    {
        this->resetLevel();
    }

    if( _gui->isFinishSet() )
    {
        auto levelFilename = MenuSelections::getInstance()->getLevelFilename();
        Common::XMLStorage::getInstance()->set("level_status", levelFilename, "finished");
        this->showFinishMenu();
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
        _gamePaused = false;
    }
    else
    {
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
    _gui->resetGUI(_players);
    Backend::Mediator::getInstance()->resetState();

    // Backend init
    this->initControlledSprite();
}

//
void LevelLayer::showFinishMenu()
{
    // Pase game
    _gamePaused = true;

    Size visibleSize = Director::sharedDirector()->getVisibleSize();

    // Create new layer
    LayerColor *lc = new LayerColor();
    int lcWidth = (int)visibleSize.width*0.75;
    int lcHeight = (int)visibleSize.width*0.60;
    lc->initWithColor( ccc4(10, 10, 10, 180), lcWidth, lcHeight);
    lc->setPosition(
        visibleSize.width/2 - lcWidth/2,
        visibleSize.height/2 - lcHeight/2
    );

    // Create menu
    Menu* menu = Menu::create();

    // Back to Main menu label
    ccMenuCallback callback = std::bind(&LevelLayer::backToLevelSelect, this);

    MenuItemFont *backToMenu = new MenuItemFont();
    backToMenu->initWithString(
        "Back to Levels",
        callback
    );
    backToMenu->setPosition(ccp(0, 0));
    menu->addChild(backToMenu);

    menu->setPosition(
        ccp(
            lcWidth/2,
            lcHeight/2
        )
    );

    // Add menu to the new layer
    lc->addChild(menu, 1);

    // Show new layer
    this->addChild(lc, 10);
}

//
void LevelLayer::backToMenu()
{
    // Replace actual scene (game) with menu and release game layer
    Scene *actualScene = Director::sharedDirector()->getRunningScene();
    Scene *pScene = MainMenuLayer::scene();
    Director::sharedDirector()->replaceScene(pScene);

    // Remove game layer
    actualScene->stopAllActions();
    actualScene->removeFromParent();
}

void LevelLayer::backToLevelSelect()
{
    // Replace actual scene (game) with menu and release game layer
    Scene *actualScene = Director::sharedDirector()->getRunningScene();
    Scene *pScene = LevelSelectLayer::scene();
    Director::sharedDirector()->replaceScene(pScene);

    // Remove game layer
    actualScene->stopAllActions();
    actualScene->removeFromParent();
}

//
void LevelLayer::initControlledSprite()
{
    // TODO: some better solution that takes into account variable IDs

    // spawnpoint is calculated on backend
    auto player1Sprite = Backend::Mediator::getInstance()->getPlayer1Sprite();
    _players[19991]->setPosition(
        ccp(
            player1Sprite->getPosition().x,
            player1Sprite->getPosition().y
        )
    );
    _players[19991]->setNextPosition(_players[19991]->getPosition());
    _players[19991]->setSpeed(player1Sprite->getAttributes()->getSpeed());

    // set view that timmy is in the center of it
    Size visibleSize = Director::sharedDirector()->getVisibleSize();
    _map->setPosition(
        ccp(
            visibleSize.width/2 - _players[19991]->getPosition().x,
            visibleSize.height/2 - _players[19991]->getPosition().y
        )
    );

    // player 2
    if(_players.size() == 2)
    {
        auto player2Sprite = Backend::Mediator::getInstance()->getPlayer2Sprite();
        _players[19992]->setPosition(
            ccp(
                player2Sprite->getPosition().x,
                player2Sprite->getPosition().y
            )
        );
        _players[19992]->setNextPosition(_players[19992]->getPosition());
        _players[19992]->setSpeed(player2Sprite->getAttributes()->getSpeed());
    }
}

//
void LevelLayer::initControlLayer()
{
    //_controlLayer->enableJoystick();
    _controlLayer->enableKeyboard();
    _controlLayer->setPauseGameDelegate(this);

    // TODO: some better solution that takes into account variable IDs
    _controlLayer->setControlledPlayer1(_players[19991]);
    if(_players.size() == 2)
    {
        _controlLayer->setControlledPlayer2(_players[19992]);
    }
}
