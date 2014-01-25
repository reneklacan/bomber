#ifndef __BOMBER_BACKEND_ACTION
#define __BOMBER_BACKEND_ACTION

#include "../../Common/Primitives/Coordinates.h"
#include "ScriptedSprite.h"

namespace Bomber
{
    namespace Backend
    {
        class Action
        {
            public:
                Action() { _complete = false; };

                virtual void update(float dt) {};
                bool isComplete() { return _complete; };
                virtual bool isLast() { return false; };
                void setSprite(ScriptedSprite *sprite) { _sprite = sprite; };

            protected:
                ScriptedSprite *_sprite;
                bool _complete;
        };

        class GoToDirection : public Action
        {
            public:
                virtual void update(float dt);

            protected:
                Common::Coordinates _destination;
                int _direction;
                int _steps;
        };

        // temporary for prototyping -> I plan to move them into separete files
        class GoUp : public GoToDirection
        {
            public:
                GoUp() { _direction = Common::UP; _steps = 1; };
                GoUp(int steps) { _direction = Common::UP; _steps = steps; };
        };

        class GoDown : public GoToDirection
        {
            public:
                GoDown() { _direction = Common::DOWN; _steps = 1; };
                GoDown(int steps) { _direction = Common::DOWN; _steps = steps; };
        };

        class GoLeft : public GoToDirection
        {
            public:
                GoLeft() { _direction = Common::LEFT; _steps = 1; };
                GoLeft(int steps) { _direction = Common::LEFT; _steps = steps; };
        };

        class GoRight : public GoToDirection
        {
            public:
                GoRight() { _direction = Common::RIGHT; _steps = 1; };
                GoRight(int steps) { _direction = Common::RIGHT; _steps = steps; };
        };

        class Again : public Action
        {
            public:
                Again() {};
                virtual bool isLast() { return true; };
        };

        class Wait : public Action
        {
            public:
                Wait();
                Wait(float period);
                virtual void update(float dt);

            private:
                float _period;
                float _expired;
        };

        class WalkTo : public Action
        {
            public:
                WalkTo(unsigned int x, unsigned int y);
                virtual void update(float dt);

            private:
                Common::Coordinates _destination;
        };

        class WalkWithoutAttentionTo : public Action
        {
            public:
                WalkWithoutAttentionTo(unsigned int x, unsigned int y);
                virtual void update(float dt);

            private:
                Common::Coordinates _destination;
        };

        class HuntNearestPlayer : public Action
        {
            public:
                HuntNearestPlayer() {};
                virtual void update(float dt);
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
