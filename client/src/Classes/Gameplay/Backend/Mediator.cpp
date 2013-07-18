
#include "Mediator.h"
#include "GameObjects/Sprites/Bomber.h"

using namespace Bomber::Backend;

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

Sprite *Mediator::getControlledSprite()
{
    // TODO:
    // - set spawn position by position in tilemap
    // - dont create new sprite each call of this method
    // - this method should be maybe called with id as argument?

    Sprite *controlledSprite = new Bomber(); 
    controlledSprite->setId(19991);
    controlledSprite->setSize(10, 10);
    controlledSprite->setPosition(200, 200);
    
    Logic::getInstance()->getState()->getSpriteLayer()->addObject(controlledSprite);
    Logic::getInstance()->setControlledSprite(controlledSprite->getId());

    return controlledSprite;
}

void Mediator::moveSprite(Position position)
{
    Logic::getInstance()->moveSprite(position);
}

void Mediator::spawnBomb()
{
    Logic::getInstance()->spawnBomb();
}

void Mediator::pushObstacle(Coordinates coords, TDirection direction)
{
    Logic::getInstance()->pushBlock(coords, direction);
}

void Mediator::kickBomb(Coordinates coords, TDirection direction)
{
    //std::cout << "KICK: [" << coords.x << ", " << coords.y << "] direction = " << direction << "\n";
    if(direction != Backend::CALM)
    {
        Logic::getInstance()->kickBomb(coords, direction);
    }
}
