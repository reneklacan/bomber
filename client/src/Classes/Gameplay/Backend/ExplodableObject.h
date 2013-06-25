#ifndef __BOMBER_BACKEND_EXPLODABLE_OBJECT
#define __BOMBER_BACKEND_EXPLODABLE_OBJECT

#include "GameObject.h"

namespace Bomber
{
    namespace Backend
    {
        class ExplodableObject : public GameObject
        {
            public:
                virtual bool isDetonated() { return false; };
                virtual bool isExplodable() { return true; };
                virtual unsigned int getOwner() { return _owner; };
                virtual unsigned int getPower() { return _power; };
                virtual unsigned int getPenetration() { return _penetration; };

            protected:
                bool _detonated;
                float _expired;
                float _timeout;
                unsigned int _power;
                unsigned int _penetration;
                unsigned int _owner;
        };
    }
}

#endif
