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
                inline virtual TCachableObjectType getObjectType() { return COT_SWITCH; };

                Switch() : GameObject()
                ,_oneTime(false)
                ,_bombSensitive(false)
                ,_passingSensitive(false)
                {

                }

                inline bool isOneTime() { return _oneTime; };
                inline bool isBombSensitive() { return _bombSensitive; };
                inline bool isPassingSensitive() { return _passingSensitive; };

            private:
                SYNTHESIZE(bool, _oneTime, OneTime);
                SYNTHESIZE(bool, _bombSensitive, BombSensitive);
                SYNTHESIZE(bool, _passingSensitive, PassingSensitive);
        };
    }
}

#endif