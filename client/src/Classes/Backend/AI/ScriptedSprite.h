#ifndef __BOMBER_BACKEND_SCRIPTED_SPRITE
#define __BOMBER_BACKEND_SCRIPTED_SPRITE

#include "../GameObjects/Sprites/Sprite.h"

namespace Bomber
{
    namespace Backend
    {
        class ScriptedSprite : public Sprite
        {
            public:
                virtual void update(float dt) = 0;

                virtual bool continueMove() = 0;
                virtual bool continueMoveTo(Common::Coordinates coords) = 0;
                virtual void goRandom() = 0;
                virtual bool tryToChasePlayer() = 0;
                virtual void tryToChasePlayerOrGoRandom() = 0;

                inline virtual bool isAI() { return true; };
                inline virtual bool isMoving() { return _moving; };

            protected:
                Common::Position _goal;
                float _step;
                bool _moving;
                SYNTHESIZE(bool, _smart, Smart); // if AI is able to find path if obstacles are in direct path
                SYNTHESIZE(float, _aggroDistance, AggroDistance);
        };
    }
}

#endif
