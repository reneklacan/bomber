#include "LevelLayer.h"
#include "../Constants.h"
#include "../Common/Storage/XMLStorage.h"
#include "../Backend/Mediator.h"
#include "../Backend/GameObjects/Sprites/Bomber.h"
#include "Buttons/GameButton.h"
#include "Layers/ButtonLayer.h"
#include "Buttons/ControlButton.h"
#include "Primitives/MenuHelper.h"
#include "../Menu/LevelSelectLayer.h"
#include "../Menu/MainMenuLayer.h"
#include "../Common/Utils.h"

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
    _statistics = new Statistics();
    _layers = new Layers();

    // Init Mediator according to connection type
    Backend::Mediator::getInstance()->setConnectionType( MenuSelections::getInstance()->getConnection() );
    
    // Batch Node Init
    _spriteBatchNode = SpriteBatchNode::create("tiles/new_tileset.png");

    // Player init
    unsigned int playerID = 19990;
    for(int i = 0; i < MenuSelections::getInstance()->getNumPlayers(); i++)
    {
        playerID++;
        _players[playerID] = new Human(
            _spriteBatchNode->getTexture(),
            CCRectMake(32,1344,32,48)
        );
        _players[playerID]->setID(playerID);
    }

    _controlLayer = ControlLayer::create();

    this->addChild(_map);
    this->addChild(_controlLayer, 2);

    // Frontend init
    _gui->init(_map, _spriteBatchNode, _players, this, _statistics);

    // Game State init
    _gameState = new Common::GameState(_map->getWidth(), _map->getHeight());
    Backend::Mediator::getInstance()->setState(_gameState);
    _gameState->init(_map->getTiledMap());
    
    // Backend init
    this->initControlledSprite();

    // Button Layer
    ButtonLayer::getInstance()->setMainLayer(this);
    std::vector<SEL_MenuHandler> callbacks;
    callbacks.push_back(menu_selector(LevelLayer::menuCloseCallback));
    callbacks.push_back(menu_selector(LevelLayer::menuPauseCallback));
    callbacks.push_back(menu_selector(LevelLayer::menuResetCallback));
    _layers->createControlButtonLayer(callbacks, this);

    // Control Layer
    this->initControlLayer();
    this->initStatistics();

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
            player->updatePosition(nextPos);
            _statistics->noteRanUnit();
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
        _statistics->resumeLevelTimer();
        _gamePaused = false;
    }
    else
    {
        _statistics->pauseLevelTimer();
        _gamePaused = true;
    }
}

//
void LevelLayer::menuResetCallback(Object* pSender)
{
    this->resetLevel();
}

//
void LevelLayer::menuRetryCallback()
{
    _gamePaused = false;
    this->removeChildByTag(LEVEL_FINISH_TAG);

    std::vector<SEL_MenuHandler> callbacks;
    callbacks.push_back(menu_selector(LevelLayer::menuCloseCallback));
    callbacks.push_back(menu_selector(LevelLayer::menuPauseCallback));
    callbacks.push_back(menu_selector(LevelLayer::menuResetCallback));
    _layers->createControlButtonLayer(callbacks, this);
    
    this->resetLevel();
}

//
void LevelLayer::resetLevel()
{
    // "reset"
    _gui->resetGUI(_players);
    Backend::Mediator::getInstance()->resetState();

    // Backend init
    this->initControlledSprite();

    this->initStatistics();
}

//
void LevelLayer::showFinishMenu()
{
    // Pause game
    _gamePaused = true;
    _statistics->endLevelTimer();

    // Prepare callbacks
    std::vector<ccMenuCallback> callbacks;
    ccMenuCallback callback1 = std::bind(&LevelLayer::backToLevelSelect, this);
    ccMenuCallback callback2 = std::bind(&LevelLayer::menuRetryCallback, this);
    callbacks.push_back(callback1);
    callbacks.push_back(callback2);

    // Show new layer
    Layer *layer = _layers->getFinishLevelLayer(_statistics, callbacks);
    this->addChild(layer, 10, LEVEL_FINISH_TAG);
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
    _players[19991]->updateDefaultImage(
        Shapes::pickImageFromTexture(
            Common::convertGidToNew(HUMAN_IMAGE_ID)
        )
    );
    _players[19991]->spawnPosition(
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
            //visibleSize.width/2 - _players[19991]->getPosition().x,
            //visibleSize.height/2 - _players[19991]->getPosition().y
            visibleSize.width/2 - _players[19991]->getPosition().x,
            //visibleSize.height/2 + 100 // why 100 and why +?
            visibleSize.height*(5.5/7.0) - _players[19991]->getPosition().y // dont know why :(
        )
    );

    // player 2
    if(_players.size() == 2)
    {
        auto player2Sprite = Backend::Mediator::getInstance()->getPlayer2Sprite();
        _players[19992]->updatePosition(
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

//
void LevelLayer::initStatistics()
{
    // Level Timer
    _statistics->startLevelTimer();
}
