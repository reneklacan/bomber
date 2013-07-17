
#ifndef __BOMBER_BACKEND_OBSTACLE
#define __BOMBER_BACKEND_OBSTACLE

#include "GameObject.h"

namespace Bomber
{
    namespace Backend
    {
        class Obstacle : public GameObject
        {
            public:
                static Obstacle *getInstanceByGid(unsigned int gid);

                Obstacle();
                void setToughness(int toughness) { _toughness = toughness; };
                inline int getToughness() { return _toughness; };
                int decreaseToughness();
                int decreaseToughness(int amount);
                inline bool isPushable() { return _pushable; };

            protected:
                int _toughness;
                bool _pushable;
        };

        class MazeBlock : public Obstacle
        {
            public:
                MazeBlock() : Obstacle()
                {
                    _name = "maze block";
                    _toughness = -1;
                }
        };

        class DestroyableBlock : public Obstacle
        {
            public:
                DestroyableBlock() : Obstacle()
                {
                    _name = "destroyable block";
                    _toughness = 1;
                }
        };

        class PushableBlock : public Obstacle
        {
            public:
                PushableBlock() : Obstacle()
                {
                    _name = "pushable block";
                    _toughness = -1;
                    _pushable = true;
                }
        };

        class LeverBlock : public Obstacle
        {
            public:
                LeverBlock() : Obstacle()
                {
                    _name = "lever";
                    _toughness = -1;
                }
        };
    }
}

#endif

