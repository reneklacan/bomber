#ifndef __BOMBER_SIZE
#define __BOMBER_SIZE

struct Size
{
    float width;
    float height;

    Size()
    {
        this->width = 0.0f;
        this->height = 0.0f;
    }

    Size(int width, int height)
    {
        this->width = width;
        this->height = height;
    }

    Size(float width, float height)
    {
        this->width = width;
        this->height = height;
    }
};

#endif
