
#include "../../Constants.h"
#include "Coordinates.h"
#include "Direction.h"

using namespace Bomber::Common;

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

bool Coordinates::operator!=(const Coordinates &other) const
{
    if (this->x == other.x && this->y == other.y)
        return false;
    return true;
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

Coordinates Coordinates::getNext(int direction)
{
    if (direction == UP)
        return Coordinates(this->x, this->y + 1);

    else if (direction == DOWN)
        return Coordinates(this->x, this->y - 1);

    else if (direction == LEFT)
        return Coordinates(this->x - 1, this->y);

    else if (direction == RIGHT)
        return Coordinates(this->x + 1, this->y);

    return *this;
}

Position Coordinates::toPosition()
{
    return Position(this->x*TILE_WIDTH, this->y*TILE_HEIGHT);
}
