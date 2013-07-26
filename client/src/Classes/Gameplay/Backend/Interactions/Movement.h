#ifndef __BOMBER_BACKEND_MOVEMENT
#define __BOMBER_BACKEND_MOVEMENT

#include "../Macros.h"
#include "../GameObjects/GameObject.h"

namespace Bomber
{
    namespace Backend
    {
        class Movement
        {
            public:
                Movement(GameObject *object, Common::Position goal, int direction, int speed);
                Movement(GameObject *object, Common::Coordinates goalCoords, int direction, int speed);
                void update(float dt);
                inline bool isFinished() { return _finished; };

            private:
                SYNTHESIZE(bool, _finished, Finished);
                SYNTHESIZE(int, _direction, Direction);
                SYNTHESIZE(int, _speed, Speed);
                SYNTHESIZE(Common::Position, _start, Start);
                SYNTHESIZE(Common::Position, _current, Current);
                SYNTHESIZE(Common::Position, _goal, Goal);
                SYNTHESIZE(GameObject *, _object, Object);
        };
    }
}

#endif
