
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

}

void Mediator::setState(GameState *state)
{
    _state = state;
    Logic::getInstance()->setState(state);
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
