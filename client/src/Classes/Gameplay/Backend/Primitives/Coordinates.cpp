
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
    return this->getCoordsAround(1);
}

std::vector<Coordinates> Coordinates::getCoordsAround(unsigned int range)
{
    std::vector<Coordinates> around;
    around.push_back(Coordinates(this->x, this->y + range));
    around.push_back(Coordinates(this->x, this->y - range));
    around.push_back(Coordinates(this->x - range, this->y));
    around.push_back(Coordinates(this->x + range, this->y));
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
