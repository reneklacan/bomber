
#include <stdarg.h>

#include "Behaviour.h"

using namespace Bomber::Backend;

void Behaviour::test()
{
    new Behaviour(
        new WalkTo(7, 14),
        new Wait(15),
        new WalkWithoutAttention(3, 3),
        new HuntNearestPlayer(),
        new Again()
    );
}

Behaviour::Behaviour(Action *firstAction, ...)
:_currentActionIndex(-1)
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

Action *Behaviour::getCurrentAction()
{
    if (_currentActionIndex == -1)
        return nullptr;

    return _actions[_currentActionIndex];
}
