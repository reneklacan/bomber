#ifndef __BOMBER_GAMEOBJECT
#define __BOMBER_GAMEOBJECT

#include "Position.h"
#include "Coordinates.h"
#include "GameObjectEventDelegate.h"

namespace Bomber
{
    namespace Backend
    {
        class GameObject
        {
            public:
                virtual unsigned int getId() { return _id; };
                virtual void setPosition(Position position);
                virtual Position getPosition() { return _position; };
                virtual Position getNextPosition() { return _nextPosition; };
                virtual Coordinates getCoords();
                virtual Coordinates getNextCoords();
                virtual void setEventDelegate(GameObjectEventDelegate* delegate);

            private:
                GameObjectEventDelegate *_eventDelegate;
                Position _position;
                Position _nextPosition;
                unsigned int _id;
        };
    }
}

#endif
