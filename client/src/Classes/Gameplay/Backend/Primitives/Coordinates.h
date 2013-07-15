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

                bool operator==(const Coordinates &other) const;
                bool operator!=(const Coordinates &other) const;

                std::vector<Coordinates> getCoordsAround();
                std::vector<Coordinates> getCoordsAround(unsigned int range);
                Coordinates getNext(int direction);
        };
    }
}

#endif
