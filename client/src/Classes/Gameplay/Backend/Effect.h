#ifndef __BOMBER_BACKEND_EFFECT
#define __BOMBER_BACKEND_EFFECT

#include <stdio.h>

#include "Sprite.h"

namespace Bomber
{
    namespace Backend
    {
        enum TEffectType
        {
            EFFECT_NONE,

            EFFECT_FLAME_INC,
            EFFECT_BOMB_CAPACITY_INC,
            EFFECT_PORTABILITY_ON,
            EFFECT_PORTABILITY_OFF,
            EFFECT_HEALTH_INC,
            EFFECT_HEALTH_DEC,
        };

        class Effect : public GameObject
        {
            public:
                Effect()
                {
                    _name = "effect none";
                    _type = EFFECT_NONE;
                };
                virtual void applyToSprite(Sprite *sprite) = 0;
                virtual void log()
                {
                    printf("effect log: %s\n", _name);
                }

            private:
                SYNTHESIZE(TEffectType, _type, Type);
        };

        class EffectFlameInc : public Effect
        {
            public:
                EffectFlameInc()
                {
                    _name = "effect flame inc";
                    _type = EFFECT_FLAME_INC;
                };
                virtual void applyToSprite(Sprite *sprite)
                {
                    sprite->getAttributes().increaseFlame();
                }
        };

        class EffectBombCapacityInc : public Effect
        {
            public:
                EffectBombCapacityInc()
                {
                    _name = "effect bomb cap inc";
                    _type = EFFECT_BOMB_CAPACITY_INC;
                };
                virtual void applyToSprite(Sprite *sprite)
                {
                    sprite->getAttributes().increaseBombCapacity();
                }
        };

        class EffectPortabilityOn : public Effect
        {
            public:
                EffectPortabilityOn()
                {
                    _name = "effect portability on";
                    _type = EFFECT_PORTABILITY_ON;
                };
                virtual void applyToSprite(Sprite *sprite)
                {
                    sprite->getAttributes().setPortability(true);
                }
        };

        class EffectPortabilityOff : public Effect
        {
            public:
                EffectPortabilityOff()
                {
                    _name = "effect portability off";
                    _type = EFFECT_PORTABILITY_OFF;
                };
                virtual void applyToSprite(Sprite *sprite)
                {
                    sprite->getAttributes().setPortability(false);
                }
        };

        class EffectHealthInc : public Effect
        {
            public:
                EffectHealthInc()
                {
                    _name = "effect heath inc";
                    _type = EFFECT_HEALTH_INC;
                };
                virtual void applyToSprite(Sprite *sprite)
                {
                    sprite->getAttributes().increaseHealth();
                }
        };

        class EffectHealthDec : public Effect
        {
            public:
                EffectHealthDec()
                {
                    _name = "effect heath dec";
                    _type = EFFECT_HEALTH_DEC;
                };
                virtual void applyToSprite(Sprite *sprite)
                {
                    sprite->getAttributes().decreaseHealth();
                }
        };
    }
}

#endif
