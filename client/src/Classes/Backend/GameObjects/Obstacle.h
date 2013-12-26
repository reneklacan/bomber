
#ifndef __BOMBER_BACKEND_OBSTACLE
#define __BOMBER_BACKEND_OBSTACLE

#include "GameObject.h"
#include <iostream>

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
                inline virtual Common::TCachableObjectType getObjectType() { return Common::COT_MAZE_BLOCK; };

                MazeBlock() : Obstacle()
                {
                    _name = "maze block";
                    this->init();
                }

                virtual void init()
                {
                    _toughness = -1;
                }
        };

        class DestroyableBlock : public Obstacle
        {
            public:
                inline virtual Common::TCachableObjectType getObjectType() { return Common::COT_DESTROYABLE_BLOCK; };

                DestroyableBlock() : Obstacle()
                {
                    _name = "destroyable block";
                    this->init();
                }

                virtual void init()
                {
                    _name = "destroyable block";
                    _toughness = 1;
                }
        };

        class PushableBlock : public Obstacle
        {
            public:
                inline virtual Common::TCachableObjectType getObjectType() { return Common::COT_PUSHABLE_BLOCK; };

                PushableBlock() : Obstacle()
                {
                    _name = "pushable block";
                    _pushable = true;
                    this->init();
                }

                virtual void init()
                {
                    _toughness = -1;
                }
        };

        class LeverBlock : public Obstacle
        {
            public:
                inline virtual Common::TCachableObjectType getObjectType() { return Common::COT_LEVER_BLOCK; };

                LeverBlock() : Obstacle()
                {
                    _name = "lever";
                    this->init();
                }

                virtual void init()
                {
                    _toughness = -1;
                }
        };
    }
}

#endif

