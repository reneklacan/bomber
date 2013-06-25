
#include "Rectangle.h"

Position rectangleGetCenterPosition(Rectangle &rectangle)
{
    Position center(
            rectangle.x + rectangle.width/2,
            rectangle.y + rectangle.height/2
    );
    return center;
}

bool rectangleIntersect(Rectangle &r1, Rectangle &r2)
{
    return !(
            r1.x > r2.x + r2.width ||
            r2.x > r1.x + r1.width ||
            r2.y > r1.y + r2.height ||
            r1.y > r2.y + r1.height
    );
}
