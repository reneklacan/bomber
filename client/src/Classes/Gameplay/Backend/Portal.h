#ifndef __BOMBER_BACKEND_PORTAL
#define __BOMBER_BACKEND_PORTAL

#include "GameObject.h"
#include "Macros.h"

namespace Bomber
{
    namespace Backend
    {
        class Portal : public GameObject
        {
            public:
                Portal();
                void configure(int top, int bottom, int left, int right);
                int getPortalTarget(Coordinates coords);

            private:
                SYNTHESIZE(int ,_topTarget, TopTarget);
                SYNTHESIZE(int ,_bottomTarget, BottomTarget);
                SYNTHESIZE(int ,_leftTarget, LeftTarget);
                SYNTHESIZE(int ,_rightTarget, RightTarget);
        };
    }
}

#endif
