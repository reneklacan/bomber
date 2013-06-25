#ifndef __BOMBER_RECTANGLE
#define __BOMBER_RECTANGLE

#include "Position.h"
#include "Size.h"

struct Rectangle
{
    float x;
    float y;
    float width;
    float height;

    Rectangle(int x, int y, int width, int height)
    {
        this->x = x;
        this->y = y;
        this->width = width;
        this->height = height;
    }

    Rectangle(float x, float y, int width, int height)
    {
        this->x = x;
        this->y = y;
        this->width = width;
        this->height = height;
    }

    Rectangle(float x, float y, float width, float height)
    {
        this->x = x;
        this->y = y;
        this->width = width;
        this->height = height;
    }

    Rectangle(Position p, Size s)
    {
        this->x = p.x;
        this->y = p.y;
        this->width = s.width;
        this->height = s.height;
    }

    bool operator==(const Rectangle &other) const
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
};

Position rectangleGetCenterPosition(Rectangle &rectangle);
bool rectangleIntersect(Rectangle &r1, Rectangle &r2);

#endif
