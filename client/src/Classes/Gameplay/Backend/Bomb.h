#ifndef __BOMBER_BACKEND_BOMB
#define __BOMBER_BACKEND_BOMB

#include "GameObject.h"

namespace Bomber
{
    namespace Backend
    {
        class Bomb : public GameObject
        {
            public:
                Bomb();
                void update(float dt);
                bool isDetonated() { return _detonated; };

            private:
                float _expired;
                bool _detonated;
                int _power;
                int _penetration;
                float _timeout;
                unsigned int _owner;
        };
    }
}

#endif
