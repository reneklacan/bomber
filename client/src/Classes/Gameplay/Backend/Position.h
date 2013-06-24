#ifndef __BOMBER_POSITION
#define __BOMBER_POSITION

struct Position
{
    float x;
    float y;

    bool operator==(const Position &other) const
    {
        if (this->x == other.x && this->y == other.y)
            return true;
        return false;
    }
};

#endif
