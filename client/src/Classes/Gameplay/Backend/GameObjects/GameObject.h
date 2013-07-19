#ifndef __BOMBER_GAMEOBJECT
#define __BOMBER_GAMEOBJECT

#include "../Macros.h"
#include "../Primitives/Position.h"
#include "../Primitives/Coordinates.h"
#include "../Primitives/Size.h"
#include "../Primitives/Rectangle.h"
#include "../Primitives/Circle.h"

namespace Bomber
{
    namespace Backend
    {
        class GameObject
        {
            public:
                GameObject();
                virtual void update(float dt) {};
                bool collides(GameObject *object);
                
                virtual void setPosition(int x, int y);
                virtual void setPosition(Position position);
                virtual void setSize(int width, int height);
                virtual void setSize(Size size);
                virtual Position &getPosition() { return _position; };
                virtual Coordinates getCoords();
                virtual bool isBombPotent() { return false; };
                virtual bool isExplodable() { return false; };
                bool isInMovement() { return _inMovement; };
                bool isDirty() { return _dirty; };
                void setDirty(bool dirty) { _dirty = dirty; };
                bool isActive() { return _active; };
                void setActive(bool active) { _active = active; };

                virtual Rectangle getCollisionRect() { return Rectangle(_position, _size); };
                virtual Circle getCollisionCircle() { return Circle(_position, _size); };
                virtual bool hasCircleCollider() { return _circleCollider; };

            protected:
                Position _position;
                Size _size;
                bool _circleCollider;
                bool _dirty;
                bool _active;
                SYNTHESIZE(bool, _inMovement, InMovement);
                SYNTHESIZE(bool, _madeCoordsAction, MadeCoordsAction);
                SYNTHESIZE(const char *, _name, Name);
                SYNTHESIZE(unsigned int, _id, Id);
                SYNTHESIZE(unsigned int, _gid, Gid);
                SYNTHESIZE(Coordinates, _currentCoords, CurrentCoords);
                SYNTHESIZE(Coordinates, _previousCoords, PreviousCoords);
        };
    }
}

#endif
