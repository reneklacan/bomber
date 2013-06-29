
#include "Coordinates.h"

Coordinates::Coordinates()
{
    this->x = 0;
    this->y = 0;
}

Coordinates::Coordinates(unsigned int x, unsigned int y)
{
    this->x = x;
    this->y = y;
}

bool Coordinates::operator==(const Coordinates &other) const
{
    if (this->x == other.x && this->y == other.y)
        return true;
    return false;
}
