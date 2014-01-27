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
                inline virtual Common::TCachableObjectType getObjectType() { return Common::COT_BOMB_POWER_INC; };

                EffectBombPowerInc() : Effect()
                {
                    _name = "effect flame inc";
                    _type = EFFECT_BOMB_POWER_INC;
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
                inline virtual Common::TCachableObjectType getObjectType() { return Common::COT_BOMB_CAPACITY_INC; };

                EffectBombCapacityInc() : Effect()
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
                inline virtual Common::TCachableObjectType getObjectType() { return Common::COT_PORTABILITY_ON; };

                EffectPortabilityOn() : Effect()
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
                inline virtual Common::TCachableObjectType getObjectType() { return Common::COT_PORTABILITY_OFF; };

                EffectPortabilityOff() : Effect()
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
                inline virtual Common::TCachableObjectType getObjectType() { return Common::COT_HEALTH_INC; };

                EffectHealthInc() : Effect()
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
                inline virtual Common::TCachableObjectType getObjectType() { return Common::COT_HEALTH_DEC; };

                EffectHealthDec() : Effect()
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
                virtual void applyToSprite(Sprite *sprite)
                {
                    sprite->getAttributes()->increaseSpeed();
                    _charges -= 1;
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
                virtual void applyToSprite(Sprite *sprite)
                {
                    sprite->getAttributes()->decreaseSpeed();
                    _charges -= 1;
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
                virtual void applyToSprite(Sprite *sprite)
                {
                    if (sprite->isAI())
                        return;

                    sprite->getAttributes()->increaseLevelKeys();
                    _charges -= 1;
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
                virtual void applyToSprite(Sprite *sprite)
                {
                    if (sprite->isAI() || sprite->getAttributes()->getFireImmunity())
                        return;

                    sprite->getAttributes()->setFireImmunity(true);
                    _charges -= 1;
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
                virtual void applyToSprite(Sprite *sprite)
                {
                    if (sprite->isAI() || sprite->getAttributes()->getWaterImmunity())
                        return;

                    sprite->getAttributes()->setWaterImmunity(true);
                    _charges -= 1;
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
                virtual void applyToSprite(Sprite *sprite)
                {
                    if (sprite->isAI())
                        return;

                    sprite->getAttributes()->setWaterImmunity(false);
                    sprite->getAttributes()->setFireImmunity(false);
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
                virtual void applyToSprite(Sprite *sprite)
                {
                    if (sprite->isAI())
                        return;

                    if (!sprite->getAttributes()->getFireImmunity())
                        sprite->getAttributes()->decreaseHealth(9999);
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
                virtual void applyToSprite(Sprite *sprite)
                {
                    if (sprite->isAI())
                        return;

                    if (!sprite->getAttributes()->getWaterImmunity())
                        sprite->getAttributes()->decreaseHealth(9999);
                }
        };
    }
}

#endif
