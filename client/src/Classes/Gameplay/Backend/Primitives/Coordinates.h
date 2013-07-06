#ifndef __BOMBER_COORDINATES
#define __BOMBER_COORDINATES

#include <vector>

namespace Bomber
{
    namespace Backend
    {
        class Coordinates
        {
            public:
                int x;
                int y;

                Coordinates();
                Coordinates(unsigned int x, unsigned int y);
                std::vector<Coordinates> getCoordsAround();

                bool operator==(const Coordinates &other) const;
                bool operator!=(const Coordinates &other) const;
        };
    }
}

#endif
