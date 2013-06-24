#ifndef __BOMBER_COORDINATES
#define __BOMBER_COORDINATES

struct Coordinates
{
    int x;
    int y;

    bool operator==(const Coordinates &other) const
    {
        if (this->x == other.x && this->y == other.y)
            return true;
        return false;
    }
};

#endif
