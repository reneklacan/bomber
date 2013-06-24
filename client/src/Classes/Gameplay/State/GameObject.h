#ifndef __BOMBER_GAMEOBJECT
#define __BOMBER_GAMEOBJECT

#include "Position.h"
#include "Coordinates.h"
#include "GameObjectEventDelegate.h"

class GameObject
{
    public:
        virtual void setRawPosition(Position position);
        virtual Position getRawPosition();
        virtual Position getNextRawPosition();
        virtual Coordinates getCoords();
        virtual Coordinates getNextCoords();
        virtual void setEventDelegate(GameObjectEventDelegate* delegate)
        {
            _eventDelegate = delegate;
        }

    private:
        GameObjectEventDelegate *_eventDelegate;
};

#endif
