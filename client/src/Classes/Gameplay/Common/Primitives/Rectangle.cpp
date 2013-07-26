
#include "Rectangle.h"

using namespace Bomber::Common;

Rectangle::Rectangle(int x, int y, int width, int height)
{
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->center = Position(x + width/2, y + height/2);
}

Rectangle::Rectangle(float x, float y, int width, int height)
{
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->center = Position(x + width/2, y + height/2);
}

Rectangle::Rectangle(float x, float y, float width, float height)
{
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->center = Position(x + width/2, y + height/2);
}

Rectangle::Rectangle(Position p, Size s)
{
    this->x = p.x;
    this->y = p.y;
    this->width = s.width;
    this->height = s.height;
    this->center = Position(x + width/2, y + height/2);
}

bool Rectangle::operator==(const Rectangle &other) const
{
    if (this->x != other.x)
        return false;
    if (this->y != other.y)
        return false;
    if (this->width != other.width)
        return false;
    if (this->height != other.height)
        return false;
    return true;

}

Position &Rectangle::getCenterPosition()
{
    return this->center;
}

void Rectangle::calculateCenterPosition()
{
    this->center = Position(
            this->x + this->width/2,
            this->y + this->height/2
    );
}

bool Rectangle::isIntersecting(Rectangle r)
{
    return !(
            this->x > r.x + r.width ||
            r.x > this->x + this->width ||
            r.y > this->y + r.height ||
            this->y > r.y + this->height
    );
}
