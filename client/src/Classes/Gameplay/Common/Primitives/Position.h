#ifndef __BOMBER_POSITION
#define __BOMBER_POSITION

#include "Direction.h"

namespace Bomber
{
    namespace Common
    {
        class Position
        {
            // TODO: move code to the separate cpp file
            public:
                float x;
                float y;

                Position()
                {
                    this->x = 0.0f;
                    this->y = 0.0f;
                }

                Position(int x, int y)
                {
                    this->x = x;
                    this->y = y;
                }

                Position(float x, float y)
                {
                    this->x = x;
                    this->y = y;
                }

                Position operator-(const Position &other) const
                {
                    return Position(this->x - other.x, this->y - other.y);
                }

                Position operator+(const Position &other) const
                {
                    return Position(this->x + other.x, this->y + other.y);
                }

                bool operator<(const float &other) const
                {
                    if (this->x < other && this->y < other)
                        return true;
                    return false;
                }

                bool operator>(const float &other) const
                {
                    if (this->x > other && this->y > other)
                        return true;
                    return false;
                }

                bool operator==(const Position &other) const
                {
                    if (this->x == other.x && this->y == other.y)
                        return true;
                    return false;
                }

                Position getNext(float step, int direction)
                {
                    if (direction == UP)
                        return Position(this->x, this->y + step);

                    if (direction == DOWN)
                        return Position(this->x, this->y - step);

                    if (direction == LEFT)
                        return Position(this->x - step, this->y);

                    if (direction == RIGHT)
                        return Position(this->x + step, this->y);

                    return *this;
                }
        };
    }
}

#endif
