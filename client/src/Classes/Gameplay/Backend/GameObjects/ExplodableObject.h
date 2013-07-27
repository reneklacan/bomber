#ifndef __BOMBER_BACKEND_EXPLODABLE_OBJECT
#define __BOMBER_BACKEND_EXPLODABLE_OBJECT

#include "GameObject.h"
#include "../../Macros.h"

namespace Bomber
{
    namespace Backend
    {
        class ExplodableObject : public GameObject
        {
            public:
                ExplodableObject() : GameObject() {};
                virtual bool isDetonated() { return _detonated; };
                virtual bool isExplodable() { return true; };
                virtual void detonate() { _detonated = true; };

            protected:
                bool _detonated;
                float _expired;
                SYNTHESIZE(float, _timeout, Timeout);
                SYNTHESIZE(unsigned int, _power, Power);
                SYNTHESIZE(unsigned int, _penetration, Penetration);
                SYNTHESIZE(int, _damage, Damage);
                SYNTHESIZE(int, _ownerId, OwnerId);
        };
    }
}

#endif
