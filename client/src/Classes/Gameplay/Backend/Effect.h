#ifndef __BOMBER_BACKEND_EFFECT
#define __BOMBER_BACKEND_EFFECT

#include "Sprite.h"

namespace Bomber
{
    namespace Backend
    {
        enum TEffectType
        {
            EFFECT_NONE,

            EFFECT_FLAME_INC,
            EFFECT_BOMB_CAPACITY_INC
        };

        class Effect : public GameObject
        {
            public:
                Effect()
                {
                    _name = "effect none";
                    _type = EFFECT_NONE;
                };
                virtual void applyToSprite(Sprite *sprite);

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
                    sprite->getAttributes()->increaseFlame();
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
                    sprite->getAttributes()->increaseBombCapacity();
                }
        };
    }
}

#endif
