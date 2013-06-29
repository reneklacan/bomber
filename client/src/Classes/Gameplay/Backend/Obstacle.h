
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
                void configureFromGid(unsigned int gid);
                void setToughness(int toughness) { _toughness = toughness; };
                int getToughness() { return _toughness; };
                int decreaseToughness();
                int decreaseToughness(int amount);

            private:
                int _toughness;
        };
    }
}

#endif

