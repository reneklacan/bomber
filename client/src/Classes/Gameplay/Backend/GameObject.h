#ifndef __BOMBER_GAMEOBJECT
#define __BOMBER_GAMEOBJECT

#include "Position.h"
#include "Coordinates.h"

namespace Bomber
{
    namespace Backend
    {
        class GameObject
        {
            public:
                virtual void setId(unsigned int id) { _id = id; };
                virtual unsigned int getId() { return _id; };
                virtual void update(float dt) {};
                virtual void setPosition(Position position);
                virtual void setNextPosition(Position position);
                virtual Position &getPosition() { return _position; };
                virtual Position getNextPosition() { return _nextPosition; };
                virtual Coordinates getCoords();
                virtual Coordinates getNextCoords();
                virtual bool isBombPotent() { return false; };
                virtual bool isExplodable() { return false; };

            protected:
                Position _position;
                Position _nextPosition;
                unsigned int _id;
        };
    }
}

#endif
