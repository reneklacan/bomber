#ifndef __BOMBER_BACKEND_CACHABLE_OBJECT
#define __BOMBER_BACKEND_CACHABLE_OBJECT

namespace Bomber
{
    namespace Backend
    {
        enum TCachableObjectType
        {
            COT_NONE,
            COT_GAME_OBJECT,
            COT_BOMB,
            COT_PORTAL,
            COT_PORTAL_EXIT,
        };

        class CachableObject
        {
            public:
                inline virtual TCachableObjectType getObjectType() { return COT_NONE; };

                virtual void init() {};
        };
    }
}

#endif