
#include <stdarg.h>
#include <stdio.h>

#include "Actions.h"

using namespace Bomber::Backend;
using namespace Bomber::Common;

void GoToDirection::update(float dt)
{
    if (_sprite->isMoving())
    {
        _sprite->continueMove();
        return;
    }

    if (_sprite->getCoords() == _destination)
    {
        _complete = true;
        return;
    }

    if (_steps != 0)
    {
        _destination = _sprite->getCoords();
        while (_steps > 0)
        {
            _steps--;
            printf("step\n");
            _destination = _destination.getNext(_direction);
        }
    }

    _sprite->continueMoveTo(_destination);
}

Wait::Wait()
:_period(-1.0f)
,_expired(0.0f)
{

}

Wait::Wait(float period)
:_expired(0.0f)
{
    _period = period;
}

void Wait::update(float dt)
{
    if (_period < 0.0f)
        return;

    _expired += dt;

    if (_expired > _period)
        _complete = true;
}

Actions::Actions(Action *firstAction, ...)
{
    va_list list;
    va_start(list, firstAction);

    _actions.push_back(firstAction);

    while (true)
    {
        Action *action = va_arg(list, Action *);

        if (action == nullptr)
            break;

        _actions.push_back(action);

        if (action->isLast())
            break;
    }

    va_end(list);
}

WalkTo::WalkTo(unsigned int x, unsigned int y)
{
    _destination = Coordinates(x, y);
}

void WalkTo::update(float dt)
{
    if (_sprite->isMoving())
    {
        _sprite->continueMove();
        return;
    }

    if (_sprite->getCoords() == _destination)
    {
        _complete = true;
        return;
    }

    if (!_sprite->tryToChasePlayer())
    {
        _sprite->continueMoveTo(_destination);
    }
}

WalkWithoutAttentionTo::WalkWithoutAttentionTo(unsigned int x, unsigned int y)
{
    _destination = Coordinates(x, y);
}

void WalkWithoutAttentionTo::update(float dt)
{
    if (_sprite->isMoving())
    {
        _sprite->continueMove();
        return;
    }

    if (_sprite->getCoords() == _destination)
    {
        _complete = true;
        return;
    }

    _sprite->continueMoveTo(_destination);
}

void HuntNearestPlayer::update(float dt)
{
    if (_sprite->isMoving())
    {
        _sprite->continueMove();
        return;
    }

    _sprite->tryToChasePlayerOrGoRandom();
}
