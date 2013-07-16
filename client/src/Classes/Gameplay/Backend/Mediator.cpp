
#include "Mediator.h"

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
    Logic::getInstance()->kickBomb(coords, direction);
}
