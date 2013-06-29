#ifndef __BOMBER_BACKEND_SPRITE_ATTR
#define __BOMBER_BACKEND_SPRITE_ATTR

namespace Bomber
{
    namespace Backend
    {
        class SpriteAttributes
        {
            public:
                SpriteAttributes()
                {
                    _flame = 2;
                    _bombCapacity = 1;
                }
                void increaseFlame() { _flame += 1; };
                void increaseBombCapacity() { _bombCapacity += 1; };

            private:
                int _flame;
                int _bombCapacity;
        };
    }
}

#endif
