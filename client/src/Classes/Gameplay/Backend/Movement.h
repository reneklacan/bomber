#ifndef __BOMBER_BACKEND_MOVEMENT
#define __BOMBER_BACKEND_MOVEMENT

#include "Macros.h"
#include "GameObject.h"

namespace Bomber
{
    namespace Backend
    {
        class Movement
        {
            public:
                Movement(GameObject *object, Position goal, int direction, int speed);
                Movement(GameObject *object, Coordinates goalCoords, int direction, int speed);
                void update(float dt);
                inline bool isFinished() { return _finished; };

            private:
                SYNTHESIZE(bool, _finished, Finished);
                SYNTHESIZE(int, _direction, Direction);
                SYNTHESIZE(int, _speed, Speed);
                SYNTHESIZE(Position, _start, Start);
                SYNTHESIZE(Position, _current, Current);
                SYNTHESIZE(Position, _goal, Goal);
                SYNTHESIZE(GameObject *, _object, Object);
        };
    }
}

#endif
