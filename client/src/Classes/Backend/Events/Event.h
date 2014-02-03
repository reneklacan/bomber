#ifndef __BOMBER_EVENT
#define __BOMBER_EVENT

#include <map>
#include <vector>
#include "../../Constants.h"

namespace Bomber
{
    namespace Backend
    {
        enum TEventType {
            // Distance events
            D_FROM_BITCHER,

            // Statistics events
            S_MOB_KILLED = EVENT_TYPE_SEPARATOR
        };

        class Event
        {
        public:
            Event();
            Event(int cycles, unsigned int priority);

            void addCondition(TEventType type);
            void addCondition(TEventType type, std::vector<int> params);
            void removeCondition(TEventType type);

            std::map<TEventType, std::vector<int> > &getConditions();
            int getCycles() { return (_cycles >= 0) ? _cycles : 1; }    // Value less than zero indicates infinite cycles
            unsigned int getPriority() { return _priority; }
            bool isComplete();

            void reset();

        private:
            std::map<TEventType, std::vector<int> > _conditions;
            std::map<TEventType, std::vector<int> > _backup;
            int _cycles;
            unsigned int _priority;
        };
    }
}

#endif