#include "EventManager.h"

using namespace Bomber::Backend;

EventArg::EventArg(int value)
{
    _type = PARAM_INT;
    _values.i = value;
}

EventArg::EventArg(float value)
{
    _type = PARAM_FLOAT;
    _values.f = value;
}

EventArg::EventArg(char* value)
{
    _type = PARAM_STRING;
    _values.s = value;
}

EventManager *EventManager::getInstance()
{
    static EventManager instance;
    return &instance;
}

void EventManager::subscribe(tEventType event, EventArg* arguments,
                           tSubscriptionType subscription, 
                           std::function<void(void)> callback)
{}

void EventManager::subscribe(std::vector<tEventType>& event, EventArg* arguments,
               tSubscriptionType subscription, 
               std::function<void(void)> callback)
{}

void EventManager::notify(tEventType event, EventArg* arguments,
            tSubscriptionType subscription)
{}