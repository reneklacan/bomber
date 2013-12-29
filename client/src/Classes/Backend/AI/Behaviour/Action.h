#ifndef __BOMBER_BACKEND_ACTION
#define __BOMBER_BACKEND_ACTION

#include "../../../Common/Primitives/Coordinates.h"

namespace Bomber
{
    namespace Backend
    {
        class Action
        {
            public:
                Action() {};
                bool isComplete() { return _complete; };
                virtual bool isLast() { return false; };

            private:
                bool _complete;
        };

        // temporary for prototyping -> I plan to move them into separete files
        class Again : public Action
        {
            public:
                Again() {};
                virtual bool isLast() { return true; };
        };

        class WalkTo : public Action
        {
            public:
                WalkTo(unsigned int x, unsigned int y) {};
        };

        class Wait : public Action
        {
            public:
                Wait() {};
                Wait(unsigned int period) {};

            private:
        };

        class WalkWithoutAttention : public Action
        {
            public:
                WalkWithoutAttention(int x, int y) {};
                WalkWithoutAttention(Common::Coordinates destination) {};

            private:
                Common::Coordinates _destination;
        };

        class HuntNearestPlayer : public Action
        {
            public:
                HuntNearestPlayer() {};
        };
    }
}

#endif
