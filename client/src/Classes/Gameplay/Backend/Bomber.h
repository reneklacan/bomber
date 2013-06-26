#ifndef __BOMBER_BACKEND_BOMBER
#define __BOMBER_BACKEND_BOMBER

#include "GameObject.h"

namespace Bomber
{
    namespace Backend
    {
        class Bomber : public GameObject
        {
            virtual bool isBombPotent() { return true; };
        };
    }
}

#endif
