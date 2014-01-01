
#include <stdarg.h>
#include <cmath>
#include <deque>

#include "AI.h"
#include "AdvancedAI.h"
#include "../../Constants.h"

using namespace Bomber::Backend;
using namespace Bomber::Common;

AdvancedAI::AdvancedAI()
{

}

AdvancedAI::AdvancedAI(Actions *actions)
{
    this->setActions(actions);
}

void AdvancedAI::update(float dt)
{
    _step = _attributes->getSpeed() * dt;

    Action *action = _actions[_currentActionIndex];
    action->update(dt);
    if (action->isComplete())
        this->nextAction();
}

void AdvancedAI::nextAction()
{
    _currentActionIndex++;
}

void AdvancedAI::setActions(Actions *actions)
{
    _actions = actions->all();

    for (auto action : _actions)
        action->setSprite(this);
}

void AdvancedAI::goRandom()
{
    Coordinates goalCoords = AI::getInstance()->getRandomCoordsAround(
        this->getCoords(),
        _attributes->getGhostMode()
    );
    _goal = goalCoords.toPosition();
    this->continueMove();
}

bool AdvancedAI::tryToChasePlayer()
{
    Coordinates goalCoords;
    std::deque<Coordinates> path = AI::getInstance()->findPathToNearestPlayer(
        this->getCoords(),
        _aggroDistance,
        _smart,
        _attributes->getGhostMode()
    );
    
    if (path.size() == 0)
        return false;

    goalCoords = AI::getInstance()->getRandomCoordsAround(
        this->getCoords(),
        _attributes->getGhostMode()
    );

    if (this->getCoords() == goalCoords)
        return false;

    _goal = goalCoords.toPosition();
    this->continueMove();
    return true;
}

void AdvancedAI::tryToChasePlayerOrGoRandom()
{
    if (!this->tryToChasePlayer())
        this->goRandom();
}

bool AdvancedAI::continueMoveTo(Coordinates coords)
{
    if (_moving)
    {
        this->continueMove();
        return true;
    }

    if (this->getCoords() == coords)
        return false;

    auto path = AI::getInstance()->findPath(this->getCoords(), coords, _attributes->getGhostMode(), _smart);

    if (path.size() == 0)
        return false;

    _goal = path[0].toPosition();
    return true;
}

bool AdvancedAI::continueMove()
{
    Position delta;
    Position nextPos = _position;
    std::deque<Coordinates> path;
    delta = _goal - _position;

    if (delta.x > TILE_WIDTH + 2*_step || delta.y > TILE_HEIGHT + 2*_step)
    {
        _moving = false;
        return false; // goal reached
    }
    else if (delta < 2*_step && delta > -2*_step)
    {
        _moving = false;
        return false; // goal reached
    }

    if (fabs(delta.x) > fabs(delta.y))
    {
        if (delta.x > 0.5)
            nextPos.x = _position.x + _step;
        else if (delta.x < 0.5)
            nextPos.x = _position.x - _step;
    }
    else
    {
        if (delta.y > 0.5)
            nextPos.y = _position.y + _step;
        else if (delta.y < 0.5)
            nextPos.y = _position.y - _step;
    }
    this->setPosition(nextPos);
    _moving = true;
    return true;
}
