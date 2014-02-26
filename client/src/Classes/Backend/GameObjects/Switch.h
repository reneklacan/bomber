#ifndef __BOMBER_BACKEND_SWITCH
#define __BOMBER_BACKEND_SWITCH

#include "GameObject.h"
#include "../../Macros.h"

namespace Bomber
{
    namespace Backend
    {
        class Switch : public GameObject
        {
            public:
                inline virtual Common::TCachableObjectType getObjectType() { return Common::COT_SWITCH; };

                Switch() : GameObject()
                ,_oneTime(false)
                ,_bombSensitive(false)
                ,_passingSensitive(false)
                {
                }

                inline bool isOneTime() { return _oneTime; };
                inline bool isBombSensitive() { return _bombSensitive; };
                inline bool isPassingSensitive() { return _passingSensitive; };
                inline bool isStandingSensitive() { return _standingSensitive; };
                inline bool isOn() { return _isOn; };
                inline bool isOff() { return !_isOn; };
                void setOn() { _isOn = true; };
                void setOff() { _isOn = false; };

            private:
                bool _isOn;
                SYNTHESIZE(bool, _oneTime, OneTime);
                SYNTHESIZE(bool, _bombSensitive, BombSensitive);
                SYNTHESIZE(bool, _passingSensitive, PassingSensitive);
                SYNTHESIZE(bool, _standingSensitive, StandingSensitive);
        };
    }
}

#endif
