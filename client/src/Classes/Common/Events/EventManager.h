#ifndef __BOMBER_EVENT_MANAGER
#define __BOMBER_EVENT_MANAGER

#include <map>
#include <vector>
#include <functional>
#include <string>

namespace Bomber
{
    namespace Backend
    {
        typedef enum eventType
        {
            PLAYER_KILLED,
            TIME_ELAPSED,
            TIME_TICK,
            EARTHQUAKE
        } tEventType;

        typedef enum subscriptionType
        {
            EVENT_ONE_TIME,
            EVENT_CONTINUAL
        } tSubscriptionType;

        typedef enum argumentType
        {
            PARAM_INT,
            PARAM_FLOAT,
            PARAM_STRING
        } tArgumentType;

        typedef union values
        {
            int i;
            float f;
            char* s;
        } tValues;

        class EventArg
        {
        public: 
            EventArg(int value);
            EventArg(float value);
            EventArg(char* value);

        private:
            tValues _values;
            tArgumentType _type;
        };

        class EventManager
        {
        public:
            static EventManager* getInstance();

            void subscribe(tEventType event, EventArg* arguments,
                           tSubscriptionType subscription, 
                           std::function<void(void)> callback);
            void subscribe(std::vector<tEventType>& event, EventArg* arguments,
                           tSubscriptionType subscription, 
                           std::function<void(void)> callback);
            void notify(tEventType event, EventArg* arguments,
                        tSubscriptionType subscription);

        private:
            EventManager(){};

        };
    }
}

#endif