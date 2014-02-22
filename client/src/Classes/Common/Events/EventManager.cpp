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