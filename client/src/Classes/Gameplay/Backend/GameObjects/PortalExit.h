#ifndef __BOMBER_BACKEND_PORTAL_EXIT
#define __BOMBER_BACKEND_PORTAL_EXIT

#include "GameObject.h"

namespace Bomber
{
    namespace Backend
    {
        class PortalExit : public GameObject
        {
            public:
                inline virtual Common::TCachableObjectType getObjectType() { return Common::COT_PORTAL_EXIT; };
        };
    }
}

#endif
