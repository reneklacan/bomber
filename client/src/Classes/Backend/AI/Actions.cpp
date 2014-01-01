
#include <stdarg.h>

#include "Actions.h"

using namespace Bomber::Backend;
using namespace Bomber::Common;

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

    while (true)
    {
        Action *action = va_arg(list, Action *);

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
