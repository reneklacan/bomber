#ifndef __BOMBER_BACKEND_SPRITE_ATTR
#define __BOMBER_BACKEND_SPRITE_ATTR

#include "Macros.h"

namespace Bomber
{
    namespace Backend
    {
        class SpriteAttributes
        {
            public:
                SpriteAttributes()
                {
                    _flame = 2;
                    _bombCapacity = 1;
                    _speed = 100;
                    _health = 100;
                    _damageModifier = 1;
                }
                void increaseFlame() { _flame += 1; };
                void decreaseFlame() { _flame -= 1; };
                void increaseBombCapacity() { _bombCapacity += 1; };
                void decreaseBombCapacity() { _bombCapacity -= 1; };
                void increaseSpeed() { _speed += 30; };
                void decreaseSoeed() { _speed -= 30; };

            private:
                SYNTHESIZE(int, _flame, Flame);
                SYNTHESIZE(int, _bombCapacity, BombCapacity);
                SYNTHESIZE(int, _speed, Speed);
                SYNTHESIZE(int, _health, Health);
                SYNTHESIZE(float, _damageModifier, DamageModifier);
        };
    }
}

#endif
