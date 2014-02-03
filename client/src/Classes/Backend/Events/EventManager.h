#ifndef __BOMBER_EVENT_MANAGER
#define __BOMBER_EVENT_MANAGER

#include <map>
#include <vector>
#include <functional>
#include <iostream>

#include "Event.h"

namespace Bomber
{
    namespace Backend
    {
        class EventManager
        {
        public:
            static EventManager* getInstance();

            void registerEvent(Event* event, std::function<void(void)> callback);
            void submitEvent(TEventType type);

            void checkStatisticsEvents();

        private:
            EventManager(){};

            std::map<Event*, std::function<void(void)> > _registeredEvents;
            std::map<TEventType, Event*> _registeredStatsHash;
        };
    }
}

#endif