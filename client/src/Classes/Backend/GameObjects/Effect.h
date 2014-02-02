#ifndef __BOMBER_BACKEND_EFFECT
#define __BOMBER_BACKEND_EFFECT

#include <stdio.h>

#include "Sprites/Sprite.h"

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
            EFFECT_SPEED_INC,
            EFFECT_SPEED_DEC,
            EFFECT_LEVEL_KEY,
            EFFECT_FIRE_IMMUNITY,
            EFFECT_WATER_IMMUNITY,
            EFFECT_CLEAR_IMMUNITIES,
            EFFECT_FIRE_TRAP,
            EFFECT_WATER_TRAP,
            EFFECT_SHIFT_UP,
            EFFECT_DEATH,
            EFFECT_FOG_ON,
            EFFECT_FOG_OFF,
        };

        class Effect : public GameObject
        {
            public:
                static Effect *getInstanceByGid(unsigned int gid);

                Effect() : GameObject()
                {
                    _name = "effect none";
                    _type = EFFECT_NONE;
                    this->init();
                };
                virtual void init()
                {
                    _charges = 1;
                }
                virtual bool applyToSprite(Sprite *sprite) = 0;
                virtual void log()
                {
                    printf("effect log: %s\n", _name);
                }

            private:
                SYNTHESIZE(TEffectType, _type, Type);
                SYNTHESIZE(int, _charges, Charges);
        };

        class NoEffect : public Effect
        {
            public:
                inline virtual Common::TCachableObjectType getObjectType() { return Common::COT_NO_EFFECT; };

                NoEffect() : Effect()
                {
                    _name = "no effect";
                    _type = EFFECT_NONE;
                }
                virtual bool applyToSprite(Sprite *sprite)
                {
                    return false;
                }
        };

        class EffectBombPowerInc : public Effect
        {
            public:
                inline virtual Common::TCachableObjectType getObjectType() { return Common::COT_BOMB_POWER_INC; };

                EffectBombPowerInc() : Effect()
                {
                    _name = "effect flame inc";
                    _type = EFFECT_BOMB_POWER_INC;
                };
                virtual bool applyToSprite(Sprite *sprite)
                {
                    sprite->getAttributes()->increaseBombPower();
                    _charges -= 1;
                    return true;
                }
        };

        class EffectBombCapacityInc : public Effect
        {
            public:
                inline virtual Common::TCachableObjectType getObjectType() { return Common::COT_BOMB_CAPACITY_INC; };

                EffectBombCapacityInc() : Effect()
                {
                    _name = "effect bomb cap inc";
                    _type = EFFECT_BOMB_CAPACITY_INC;
                    _charges = 1;
                };
                virtual bool applyToSprite(Sprite *sprite)
                {
                    sprite->getAttributes()->increaseBombCapacity();
                    _charges -= 1;
                    return true;
                }
        };

        class EffectPortabilityOn : public Effect
        {
            public:
                inline virtual Common::TCachableObjectType getObjectType() { return Common::COT_PORTABILITY_ON; };

                EffectPortabilityOn() : Effect()
                {
                    _name = "effect portability on";
                    _type = EFFECT_PORTABILITY_ON;
                    _charges = 1;
                };
                virtual bool applyToSprite(Sprite *sprite)
                {
                    sprite->getAttributes()->setPortability(true);
                    _charges -= 1;
                    return true;
                }
        };

        class EffectPortabilityOff : public Effect
        {
            public:
                inline virtual Common::TCachableObjectType getObjectType() { return Common::COT_PORTABILITY_OFF; };

                EffectPortabilityOff() : Effect()
                {
                    _name = "effect portability off";
                    _type = EFFECT_PORTABILITY_OFF;
                    _charges = 1;
                };
                virtual bool applyToSprite(Sprite *sprite)
                {
                    sprite->getAttributes()->setPortability(false);
                    _charges -= 1;
                    return true;
                }
        };

        class EffectHealthInc : public Effect
        {
            public:
                inline virtual Common::TCachableObjectType getObjectType() { return Common::COT_HEALTH_INC; };

                EffectHealthInc() : Effect()
                {
                    _name = "effect heath inc";
                    _type = EFFECT_HEALTH_INC;
                    _charges = 1;
                };
                virtual bool applyToSprite(Sprite *sprite)
                {
                    sprite->getAttributes()->increaseHealth();
                    _charges -= 1;
                    return true;
                }
        };

        class EffectHealthDec : public Effect
        {
            public:
                inline virtual Common::TCachableObjectType getObjectType() { return Common::COT_HEALTH_DEC; };

                EffectHealthDec() : Effect()
                {
                    _name = "effect heath dec";
                    _type = EFFECT_HEALTH_DEC;
                    _charges = 1;
                };
                virtual bool applyToSprite(Sprite *sprite)
                {
                    sprite->getAttributes()->decreaseHealth();
                    _charges -= 1;
                    return true;
                }
        };

        class EffectSpeedInc : public Effect
        {
            public:
                inline virtual Common::TCachableObjectType getObjectType() { return Common::COT_SPEED_INC; };

                EffectSpeedInc() : Effect()
                {
                    _name = "effect speed inc";
                    _type = EFFECT_SPEED_INC;
                    _charges = 1;
                };
                virtual bool applyToSprite(Sprite *sprite)
                {
                    sprite->getAttributes()->increaseSpeed();
                    _charges -= 1;
                    return true;
                }
        };

        class EffectSpeedDec : public Effect
        {
            public:
                inline virtual Common::TCachableObjectType getObjectType() { return Common::COT_SPEED_DEC; };

                EffectSpeedDec() : Effect()
                {
                    _name = "effect speed inc";
                    _type = EFFECT_SPEED_DEC;
                    _charges = 1;
                };
                virtual bool applyToSprite(Sprite *sprite)
                {
                    sprite->getAttributes()->decreaseSpeed();
                    _charges -= 1;
                    return true;
                }
        };

        class EffectLevelKey : public Effect
        {
            public:
                inline virtual Common::TCachableObjectType getObjectType() { return Common::COT_LEVEL_KEY; };

                EffectLevelKey() : Effect()
                {
                    _name = "level key";
                    _type = EFFECT_LEVEL_KEY;
                    _charges = 1;
                };
                virtual bool applyToSprite(Sprite *sprite)
                {
                    if (sprite->isAI())
                        return false;

                    sprite->getAttributes()->increaseLevelKeys();
                    _charges -= 1;
                    return true;
                }
        };

        class EffectFireImmunity : public Effect
        {
            public:
                inline virtual Common::TCachableObjectType getObjectType() { return Common::COT_FIRE_IMMUNITY; };

                EffectFireImmunity() : Effect()
                {
                    _name = "fire immunity";
                    _type = EFFECT_FIRE_IMMUNITY;
                    _charges = 1;
                };
                virtual bool applyToSprite(Sprite *sprite)
                {
                    if (sprite->isAI())
                        return false;

                    _charges -= 1;

                    if (sprite->getAttributes()->getFireImmunity())
                        return false;

                    sprite->getAttributes()->setFireImmunity(true);
                    return true;
                }
        };

        class EffectWaterImmunity : public Effect
        {
            public:
                inline virtual Common::TCachableObjectType getObjectType() { return Common::COT_WATER_IMMUNITY; };

                EffectWaterImmunity() : Effect()
                {
                    _name = "water immunity";
                    _type = EFFECT_WATER_IMMUNITY;
                    _charges = 1;
                };
                virtual bool applyToSprite(Sprite *sprite)
                {
                    if (sprite->isAI())
                        return false;

                    _charges -= 1;

                    if (sprite->getAttributes()->getWaterImmunity())
                        return false;

                    sprite->getAttributes()->setWaterImmunity(true);
                    return true;
                }
        };

        class EffectClearImmunities : public Effect
        {
            public:
                inline virtual Common::TCachableObjectType getObjectType() { return Common::COT_CLEAR_IMMUNITIES; };

                EffectClearImmunities() : Effect()
                {
                    _name = "clear immunities";
                    _type = EFFECT_CLEAR_IMMUNITIES;
                    _charges = 999;
                };
                virtual bool applyToSprite(Sprite *sprite)
                {
                    if (sprite->isAI())
                        return false;

                    if (!sprite->getAttributes()->getFireImmunity() && !sprite->getAttributes()->getWaterImmunity())
                        return false;

                    sprite->getAttributes()->setWaterImmunity(false);
                    sprite->getAttributes()->setFireImmunity(false);

                    return true;
                }
        };

        class EffectFireTrap : public Effect
        {
            public:
                inline virtual Common::TCachableObjectType getObjectType() { return Common::COT_FIRE_TRAP; };

                EffectFireTrap() : Effect()
                {
                    _name = "fire trap";
                    _type = EFFECT_FIRE_TRAP;
                    _charges = 999;
                };
                virtual bool applyToSprite(Sprite *sprite)
                {
                    if (sprite->isAI())
                        return false;

                    if (!sprite->getAttributes()->getFireImmunity())
                        sprite->getAttributes()->decreaseHealth(9999);

                    return false;
                }
        };

        class EffectWaterTrap : public Effect
        {
            public:
                inline virtual Common::TCachableObjectType getObjectType() { return Common::COT_WATER_TRAP; };

                EffectWaterTrap() : Effect()
                {
                    _name = "water trap";
                    _type = EFFECT_WATER_TRAP;
                    _charges = 999;
                };
                virtual bool applyToSprite(Sprite *sprite)
                {
                    if (sprite->isAI())
                        return false;

                    if (!sprite->getAttributes()->getWaterImmunity())
                        sprite->getAttributes()->decreaseHealth(9999);

                    return false;
                }
        };

        class EffectShiftUp : public Effect
        {
            public:
                inline virtual Common::TCachableObjectType getObjectType() { return Common::COT_SHIFT_UP; };

                EffectShiftUp() : Effect()
                {
                    _name = "water trap";
                    _type = EFFECT_SHIFT_UP;
                    _charges = 999;
                };
                virtual bool applyToSprite(Sprite *sprite);
        };

        class EffectDeath : public Effect
        {
            public:
                inline virtual Common::TCachableObjectType getObjectType() { return Common::COT_SHIFT_UP; };

                EffectDeath() : Effect()
                {
                    _name = "instant death";
                    _type = EFFECT_DEATH;
                    _charges = 999;
                };
                virtual bool applyToSprite(Sprite *sprite);
        };

        class EffectFogOn : public Effect
        {
            public:
                inline virtual Common::TCachableObjectType getObjectType() { return Common::COT_FOG_ON; };

                EffectFogOn() : Effect()
                {
                    _name = "instant death";
                    _type = EFFECT_FOG_ON;
                };
                virtual bool applyToSprite(Sprite *sprite)
                {
                    _charges -= 1;
                    return false;
                }
        };

        class EffectFogOff : public Effect
        {
            public:
                inline virtual Common::TCachableObjectType getObjectType() { return Common::COT_FOG_OFF; };

                EffectFogOff() : Effect()
                {
                    _name = "instant death";
                    _type = EFFECT_FOG_OFF;
                };
                virtual bool applyToSprite(Sprite *sprite)
                {
                    _charges -= 1;
                    return false;
                }
        };
    }
}

#endif
