#ifndef __BOMBER_BACKEND_BEHAVIOUR
#define __BOMBER_BACKEND_BEHAVIOUR

#include <vector>

#include "Action.h"

namespace Bomber
{
    namespace Backend
    {
        class Behaviour
        {
            public:
                static void test();

                Behaviour();
                Behaviour(Action *action, ...);
                Action *getCurrentAction();

            private:
                std::vector<Action *> _actions;
                int _currentActionIndex;
        };
    }
}

#endif
