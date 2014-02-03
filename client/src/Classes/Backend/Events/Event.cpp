#include "Event.h"

using namespace Bomber::Backend;

Event::Event()
: _cycles(1), _priority(0)
{
    _conditions.clear();
}

Event::Event(int cycles, unsigned int priority)
: _cycles(cycles), _priority(priority)
{
    _conditions.clear();
}

void Event::addCondition(TEventType type)
{
    // params : cycles, priority, other important values of a specific event
    std::vector<int> params;
    _conditions[type] = params;
    _backup[type] = params;
}

void Event::addCondition(TEventType type, std::vector<int> params)
{
    _conditions[type] = params;
    _backup[type] = params;
}

void Event::removeCondition(TEventType type)
{
    _conditions.erase(type);
    if( isComplete() )
    {
        _cycles -= 1;
    }
}

std::map<TEventType, std::vector<int> > &Event::getConditions()
{
    return _conditions;
}

bool Event::isComplete()
{
   return _conditions.empty();
}

void Event::reset()
{
   _conditions.insert(_backup.begin(), _backup.end());
}