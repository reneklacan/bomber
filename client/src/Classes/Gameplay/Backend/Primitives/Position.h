#ifndef __BOMBER_POSITION
#define __BOMBER_POSITION

class Position
{
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

        bool operator==(const Position &other) const
        {
            if (this->x == other.x && this->y == other.y)
                return true;
            return false;
        }
};

#endif
