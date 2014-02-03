#include "EventManager.h"

using namespace Bomber::Backend;

EventManager *EventManager::getInstance()
{
    static EventManager instance;
    return &instance;
}

void EventManager::registerEvent(Event* event, std::function<void(void)> callback)
{
    _registeredEvents[event] = callback;

    // Store Statistics Events to Hash
    for( auto& condition : event->getConditions() )
    {
        if(condition.first >= EVENT_TYPE_SEPARATOR)
        {
            _registeredStatsHash[condition.first] = event;
        }
    }
}

void EventManager::submitEvent(TEventType type)
{
    std::vector<Event *> eventsToRemove; 
    for( auto& eventKV : _registeredEvents )
    {
        auto event = eventKV.first;
        bool removeCondition = false;
        TEventType conditionToRemove;
        for ( auto& condition : event->getConditions() )
        {
            if(condition.first == type)
            {
                // only one condition of each type can be present
                removeCondition = true;
                conditionToRemove = type;
                break;
            }
        }

        if(removeCondition)
        {
            // remove fulfilled condition
            event->removeCondition(conditionToRemove);
        }

        if( event->isComplete() )
        {
            // if all conditions are fulfilled execute callback
            _registeredEvents[event]();
        }

        if(event->getCycles() == 0)
        {
            // remove event after given number of cycles
            eventsToRemove.push_back(event);
        }
        else
        {
            // prepare for next cycle
            event->reset();
        }
    }

    for( auto& event : eventsToRemove )
    {
        _registeredEvents.erase(event);
    }
}

void EventManager::checkStatisticsEvents()
{
    std::cerr << "Implement checkStatisticsEvents() !\n";
}