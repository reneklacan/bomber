
#include "Mediator.h"
#include "GameObjects/Sprites/Bomber.h"
#include "Statistics/StatisticsUpdater.h"

using namespace Bomber::Backend;
using namespace Bomber::Common;
using namespace Bomber::Middend;

Mediator *Mediator::_instance = nullptr;

Mediator *Mediator::getInstance()
{
    if (_instance == nullptr)
    {
        _instance = new Mediator();
    }
    return _instance;
}

Mediator::Mediator()
{
    _gameStateUpdater = new GameStateUpdater();
    _connectionType = Common::NONE_CON;
}

void Mediator::resetState()
{
    _gameStateUpdater->resetState();
}

void Mediator::update(float dt)
{
    Logic::getInstance()->update(dt);
}

void Mediator::setState(GameState *state)
{
    _state = state;
    _gameStateUpdater->setState(state);

    Logic::getInstance()->setGameStateUpdater(_gameStateUpdater);
};

void Mediator::setControlledSprite(unsigned int id)
{
    Logic::getInstance()->setControlledSprite(id);
}

Sprite *Mediator::getPlayer1Sprite()
{
    // TODO:
    // - dont create new sprite each call of this method
    // - this method should be maybe called with id as argument?

    unsigned int id = 19991;
    unsigned int playerNumber = 1;

    Sprite *controlledSprite = new BomberSprite(); 
    controlledSprite->setId(id);
    controlledSprite->setSize(10, 10);
    
    Logic::getInstance()->getState()->getSpriteLayer()->addObject(controlledSprite);
    Logic::getInstance()->getState()->setSpawnPoint(playerNumber, id);
    StatisticsUpdater::getInstance()->setRelevantSpriteId(controlledSprite->getId());

    return controlledSprite;
}

Sprite *Mediator::getPlayer2Sprite()
{
    // TODO:
    // - dont create new sprite each call of this method
    // - this method should be maybe called with id as argument?

    unsigned int id = 19992;
    unsigned int playerNumber = 2;

    Sprite *controlledSprite = new BomberSprite(); 
    controlledSprite->setId(id);
    controlledSprite->setSize(10, 10);
    
    Logic::getInstance()->getState()->getSpriteLayer()->addObject(controlledSprite);
    Logic::getInstance()->getState()->setSpawnPoint(playerNumber, id);

    return controlledSprite;
}

void Mediator::moveSprite(unsigned int spriteId, Position position)
{
    Logic::getInstance()->moveSprite(spriteId, position);
}

void Mediator::spawnBomb(unsigned int spriteId)
{
    Logic::getInstance()->spawnBomb(spriteId);
}

// TODO: rename this method to something general like touchObstacle
void Mediator::pushObstacle(unsigned int spriteId, Coordinates coords, TDirection direction)
{
    //std::cout << "PUSH: [" << coords.x << ", " << coords.y << "] direction = " << direction << "\n";
    Logic::getInstance()->pushBlock(spriteId, coords, direction);
    Logic::getInstance()->unlockDoor(spriteId, coords);
    Logic::getInstance()->displayText(spriteId, coords);
}

void Mediator::kickBomb(unsigned int spriteId, Coordinates coords, TDirection direction)
{
    if(direction != CALM)
    {
        //std::cout << "KICK: " << spriteId << " [" << coords.x << ", " << coords.y << "] direction = " << direction << "\n";
        Logic::getInstance()->kickBomb(spriteId, coords, direction);
    }
}

void Mediator::setConnectionType(TConnectionType type)
{
    if(type == Common::NONE_CON)
    {
        _connectionType = type;
    }
    else if(type == Common::LOCAL_CON)
    {
        std::cerr << "Local game (LAN) not supported !" << std::endl;
    }
    else if(type == Common::WIDE_CON)
    {
        _client = new NetClient;
        if( _client->isRunning() )
        {
            // std::cout << "Network client started successfully.\n";
            _connectionType = type;
        }
        else
        {
           std::cerr << "Unable to start network client !" << std::endl; 
        }
    }
    else
    {
        std::cerr << "Unknown connection type !" << std::endl;
    }
}
