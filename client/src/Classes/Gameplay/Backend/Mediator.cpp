
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
