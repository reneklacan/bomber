#ifndef __BOMBER_BACKEND_ACTION
#define __BOMBER_BACKEND_ACTION

#include "../../Common/Primitives/Coordinates.h"
#include "../GameObjects/Sprites/Sprite.h"

namespace Bomber
{
    namespace Backend
    {
        class Action
        {
            public:
                Action() {};

                virtual void update(float dt) {};
                bool isComplete() { return _complete; };
                virtual bool isLast() { return false; };
                void setSprite(Sprite *sprite) { _sprite = sprite; };

            protected:
                Sprite *_sprite;
                bool _complete;
        };

        // temporary for prototyping -> I plan to move them into separete files
        class Again : public Action
        {
            public:
                Again() {};
                virtual bool isLast() { return true; };
        };

        class WalkTo : public Action
        {
            public:
                WalkTo(unsigned int x, unsigned int y) {};
        };

        class Wait : public Action
        {
            public:
                Wait();
                Wait(float period);
                virtual void update(float dt);

            private:
                float _period = -1.0f;
                float _expired = 0.0f;
        };

        class WalkWithoutAttentionTo : public Action
        {
            public:
                WalkWithoutAttentionTo(int x, int y) {};
                WalkWithoutAttentionTo(Common::Coordinates destination) {};

            private:
                Common::Coordinates _destination;
        };

        class HuntNearestPlayer : public Action
        {
            public:
                HuntNearestPlayer() {};
        };

        class Actions
        {
            public:
                Actions(Action *action, ...);
                std::vector<Action *> all() { return _actions; };

            private:
                std::vector<Action *> _actions;
        };
    }
}

#endif
