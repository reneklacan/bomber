
#include "Coordinates.h"

using namespace Bomber::Backend;

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

std::vector<Coordinates> Coordinates::getCoordsAround()
{
    std::vector<Coordinates> around;
    around.push_back(Coordinates(this->x + 1, this->y));
    around.push_back(Coordinates(this->x - 1, this->y));
    around.push_back(Coordinates(this->x, this->y + 1));
    around.push_back(Coordinates(this->x, this->y - 1));
    return around;
}

bool Coordinates::operator==(const Coordinates &other) const
{
    if (this->x == other.x && this->y == other.y)
        return true;
    return false;
}

bool Coordinates::operator!=(const Coordinates &other) const
{
    if (this->x == other.x && this->y == other.y)
        return false;
    return true;
}
