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

            EFFECT_BOMB_POWER_INC,
            EFFECT_BOMB_CAPACITY_INC,
            EFFECT_PORTABILITY_ON,
            EFFECT_PORTABILITY_OFF,
            EFFECT_HEALTH_INC,
            EFFECT_HEALTH_DEC,
        };

        class Effect : public GameObject
        {
            public:
                static Effect *getInstanceByGid(unsigned int gid);

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
                SYNTHESIZE(int, _charges, Charges);
        };

        class EffectBombPowerInc : public Effect
        {
            public:
                EffectBombPowerInc()
                {
                    _name = "effect flame inc";
                    _type = EFFECT_BOMB_POWER_INC;
                    _charges = 1;
                };
                virtual void applyToSprite(Sprite *sprite)
                {
                    sprite->getAttributes()->increaseBombPower();
                    _charges -= 1;
                }
        };

        class EffectBombCapacityInc : public Effect
        {
            public:
                EffectBombCapacityInc()
                {
                    _name = "effect bomb cap inc";
                    _type = EFFECT_BOMB_CAPACITY_INC;
                    _charges = 1;
                };
                virtual void applyToSprite(Sprite *sprite)
                {
                    sprite->getAttributes()->increaseBombCapacity();
                    _charges -= 1;
                }
        };

        class EffectPortabilityOn : public Effect
        {
            public:
                EffectPortabilityOn()
                {
                    _name = "effect portability on";
                    _type = EFFECT_PORTABILITY_ON;
                    _charges = 1;
                };
                virtual void applyToSprite(Sprite *sprite)
                {
                    sprite->getAttributes()->setPortability(true);
                    _charges -= 1;
                }
        };

        class EffectPortabilityOff : public Effect
        {
            public:
                EffectPortabilityOff()
                {
                    _name = "effect portability off";
                    _type = EFFECT_PORTABILITY_OFF;
                    _charges = 1;
                };
                virtual void applyToSprite(Sprite *sprite)
                {
                    sprite->getAttributes()->setPortability(false);
                    _charges -= 1;
                }
        };

        class EffectHealthInc : public Effect
        {
            public:
                EffectHealthInc()
                {
                    _name = "effect heath inc";
                    _type = EFFECT_HEALTH_INC;
                    _charges = 1;
                };
                virtual void applyToSprite(Sprite *sprite)
                {
                    sprite->getAttributes()->increaseHealth();
                    _charges -= 1;
                }
        };

        class EffectHealthDec : public Effect
        {
            public:
                EffectHealthDec()
                {
                    _name = "effect heath dec";
                    _type = EFFECT_HEALTH_DEC;
                    _charges = 1;
                };
                virtual void applyToSprite(Sprite *sprite)
                {
                    sprite->getAttributes()->decreaseHealth();
                    _charges -= 1;
                }
        };
    }
}

#endif
