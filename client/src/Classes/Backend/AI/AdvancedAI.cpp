
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

void AdvancedAI::goToRandomDirection()
{
    Coordinates goalCoords = AI::getInstance()->getRandomCoordsAround(
        this->getCoords(),
        _attributes->getGhostMode()
    );
    _goal = Position(goalCoords.x*TILE_WIDTH, goalCoords.y*TILE_HEIGHT);
    this->continueMove();
}

void AdvancedAI::tryToChasePlayer()
{
    Coordinates goalCoords;
    std::deque<Coordinates> path = AI::getInstance()->findPathToNearestPlayer(
        this->getCoords(),
        _aggroDistance,
        _smart,
        _attributes->getGhostMode()
    );
    
    if (path.size() != 0)
    {
        goalCoords = path[0];
    }
    else
    {
        goalCoords = AI::getInstance()->getRandomCoordsAround(
            this->getCoords(),
            _attributes->getGhostMode()
        );
    }

    if (this->getCoords() == goalCoords)
        return;

    _goal = Position(goalCoords.x*TILE_WIDTH, goalCoords.y*TILE_HEIGHT);
    this->continueMove();
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
        return true; // goal reached
    }
    else if (delta < 2*_step && delta > -2*_step)
    {
        _moving = false;
        return true; // goal reached
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
    return false;
}
