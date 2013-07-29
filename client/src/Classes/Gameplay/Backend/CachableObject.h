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
            COT_SWITCH,

            // sprites
            COT_AI_SPRITE,

            // obstacles
            COT_MAZE_BLOCK,
            COT_LEVER_BLOCK,
            COT_DESTROYABLE_BLOCK,
            COT_PUSHABLE_BLOCK,

            // effects
            COT_BOMB_POWER_INC,
            COT_BOMB_CAPACITY_INC,
            COT_PORTABILITY_ON,
            COT_PORTABILITY_OFF,
            COT_HEALTH_INC,
            COT_HEALTH_DEC,
            COT_SPEED_INC,
            COT_SPEED_DEC,
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