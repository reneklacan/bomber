
#include "Mediator.h"
#include "GameObjects/Sprites/Bomber.h"
#include "Statistics/StatisticsUpdater.h"

using namespace Bomber::Backend;
using namespace Bomber::Common;

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
    // - set spawn position by position in tilemap
    // - dont create new sprite each call of this method
    // - this method should be maybe called with id as argument?

    Sprite *controlledSprite = new BomberSprite(); 
    controlledSprite->setId(19991);
    controlledSprite->setSize(10, 10);
    controlledSprite->setPosition(200, 200);
    
    Logic::getInstance()->getState()->getSpriteLayer()->addObject(controlledSprite);
    StatisticsUpdater::getInstance()->setRelevantSpriteId(controlledSprite->getId());

    return controlledSprite;
}

Sprite *Mediator::getPlayer2Sprite()
{
    // TODO:
    // - set spawn position by position in tilemap
    // - dont create new sprite each call of this method
    // - this method should be maybe called with id as argument?

    Sprite *controlledSprite = new BomberSprite(); 
    controlledSprite->setId(19992);
    controlledSprite->setSize(10, 10);
    controlledSprite->setPosition(300, 200);
    
    Logic::getInstance()->getState()->getSpriteLayer()->addObject(controlledSprite);

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

void Mediator::pushObstacle(unsigned int spriteId, Coordinates coords, TDirection direction)
{
    //std::cout << "PUSH: [" << coords.x << ", " << coords.y << "] direction = " << direction << "\n";
    Logic::getInstance()->pushBlock(spriteId, coords, direction);
}

void Mediator::kickBomb(unsigned int spriteId, Coordinates coords, TDirection direction)
{
    if(direction != CALM)
    {
        std::cout << "KICK: " << spriteId << " [" << coords.x << ", " << coords.y << "] direction = " << direction << "\n";
        Logic::getInstance()->kickBomb(spriteId, coords, direction);
    }
}
