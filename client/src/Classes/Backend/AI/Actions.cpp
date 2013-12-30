
#include <stdarg.h>

#include "Actions.h"

using namespace Bomber::Backend;

Wait::Wait()
{

}

Wait::Wait(float period)
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
