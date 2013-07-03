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
                    _portability = true;
                }
                void increaseFlame() { _flame += 1; };
                void decreaseFlame() { _flame -= 1; };
                void increaseBombCapacity() { _bombCapacity += 1; };
                void decreaseBombCapacity() { _bombCapacity -= 1; };
                void increaseSpeed() { _speed += 30; };
                void decreaseSpeed() { _speed -= 30; };
                void increaseHealth() { _health += 30; };
                void decreaseHealth() { _health -= 30; };
                void increaseHealth(int num) { _health += num; };
                void decreaseHealth(int num) { _health -= num; };
                bool isAlive() { return _health > 0; };
                bool isDead() { return _health <= 0; };

            private:
                SYNTHESIZE(int, _flame, Flame);
                SYNTHESIZE(int, _bombCapacity, BombCapacity);
                SYNTHESIZE(int, _speed, Speed);
                SYNTHESIZE(int, _health, Health);
                SYNTHESIZE(float, _damageModifier, DamageModifier);
                SYNTHESIZE(bool, _portability, Portability);
        };
    }
}

#endif
