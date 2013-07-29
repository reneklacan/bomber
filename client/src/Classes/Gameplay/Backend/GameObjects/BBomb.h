#ifndef __BOMBER_BACKEND_BOMB
#define __BOMBER_BACKEND_BOMB

#include "GameObject.h"
#include "Sprites/Sprite.h"

namespace Bomber
{
    namespace Backend
    {
        class Bomb : public GameObject
        {
            public:
                inline virtual Common::TCachableObjectType getObjectType() { return Common::COT_BOMB; };

                Bomb();
                virtual void init();
                void configure(Sprite *owner);
                void update(float dt);

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

