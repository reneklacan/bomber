#ifndef __BOMBER_GAMEOBJECT
#define __BOMBER_GAMEOBJECT

#include "../../Macros.h"
#include "../../Common/Cache/CachableObject.h"
#include "../../Common/Primitives/Position.h"
#include "../../Common/Primitives/Coordinates.h"
#include "../../Common/Primitives/Size.h"
#include "../../Common/Primitives/Rectangle.h"
#include "../../Common/Primitives/Circle.h"

namespace Bomber
{
    namespace Backend
    {
        class GameObject : public Common::CachableObject
        {
            public:
                inline virtual Common::TCachableObjectType getObjectType() { return Common::COT_GAME_OBJECT; };

                GameObject();
                virtual void update(float dt) {};
                bool collides(GameObject *object);
                
                virtual void setPosition(int x, int y);
                virtual void setPosition(Common::Position position);
                virtual void setSize(int width, int height);
                virtual void setSize(Common::Size size);
                virtual Common::Position &getPosition() { return _position; };
                virtual Common::Coordinates getCoords();
                virtual bool isBombPotent() { return false; };
                virtual bool isExplodable() { return false; };
                bool isInMovement() { return _inMovement; };
                bool isDirty() { return _dirty; };
                void setDirty(bool dirty) { _dirty = dirty; };
                bool isActive() { return _active; };
                void setActive(bool active) { _active = active; };

                virtual Common::Rectangle getCollisionRect() { return Common::Rectangle(_position, _size); };
                virtual Common::Circle getCollisionCircle() { return Common::Circle(_position, _size); };
                virtual bool hasCircleCollider() { return _circleCollider; };

            protected:
                Common::Position _position;
                Common::Size _size;
                bool _circleCollider;
                bool _dirty;
                bool _active;
                SYNTHESIZE(bool, _inMovement, InMovement);
                SYNTHESIZE(bool, _madeCoordsAction, MadeCoordsAction);
                SYNTHESIZE(const char *, _name, Name);
                SYNTHESIZE(unsigned int, _id, Id);
                SYNTHESIZE(unsigned int, _gid, Gid);
                SYNTHESIZE(Common::Coordinates, _currentCoords, CurrentCoords);
                SYNTHESIZE(Common::Coordinates, _previousCoords, PreviousCoords);
        };
    }
}

#endif
