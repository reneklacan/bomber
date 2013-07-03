#ifndef __BOMBER_RECTANGLE
#define __BOMBER_RECTANGLE

#include "Position.h"
#include "Size.h"

namespace Bomber
{
    namespace Backend
    {
        class Rectangle
        {
            public:
                float x;
                float y;
                float width;
                float height;
                Position center;

                Rectangle(int x, int y, int width, int height);
                Rectangle(float x, float y, int width, int height);
                Rectangle(float x, float y, float width, float height);
                Rectangle(Position p, Size s);

                bool operator==(const Rectangle &other) const;

                Position &getCenterPosition();
                void calculateCenterPosition();
                bool isIntersecting(Rectangle r);
        };
    }
}

#endif
