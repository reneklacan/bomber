#ifndef __BOMBER_GAMEOBJECT
#define __BOMBER_GAMEOBJECT

#include "Position.h"
#include "Coordinates.h"
#include "Size.h"
#include "Rectangle.h"
#include "Circle.h"

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
                virtual void setPosition(int x, int y);
                virtual void setPosition(Position position);
                virtual void setSize(int width, int height);
                virtual void setSize(Size size);
                //virtual void setNextPosition(Position position);
                virtual Position &getPosition() { return _position; };
                //virtual Position getNextPosition() { return _nextPosition; };
                virtual Coordinates getCoords();
                //virtual Coordinates getNextCoords();
                virtual bool isBombPotent() { return false; };
                virtual bool isExplodable() { return false; };
                bool isDirty() { return _dirty; };
                bool setDirty(bool dirty) { _dirty = dirty; }

                virtual Rectangle getCollisionRect() { return Rectangle(_position, _size); };
                virtual Circle getCollisionCircle() { return Circle(_position, _size); };

            protected:
                Position _position;
                Size _size;
                bool _sphereCollisionArea;
                //Position _nextPosition;
                unsigned int _id;
                bool _dirty;
        };
    }
}

#endif
