#ifndef __BOMBER_FRONTEND_SHAPES
#define __BOMBER_FRONTEND_SHAPES

#include "cocos2d.h"
#include "../../Constants.h"

using namespace cocos2d;

namespace Bomber
{
    namespace Frontend
    {
        class Shapes
        {
        public: 
            static Point* getBorderBox(Point point, Rect rect, int padding)
            {
                int rangeX = (rect.getMaxX()-rect.getMinX())/2;
                int rangeY = (rect.getMaxY()-rect.getMinY())/2;
                Point *ccPoints = new Point[4];
                ccPoints[0] = ccp(point.x-rangeX-padding,
                                  point.y+rangeY+padding );
                ccPoints[1] = ccp(point.x-rangeX-padding,
                                  point.y-rangeY-padding );
                ccPoints[2] = ccp(point.x+rangeX+padding,
                                  point.y-rangeY-padding );
                ccPoints[3] = ccp(point.x+rangeX+padding,
                                  point.y+rangeY+padding );
                return ccPoints;
            }

            static Rect pickImageFromTexture(unsigned int id)
            {
                id--;
                int ix = id % TEXTURE_IMAGES_PER_LINE;
                int iy = id / TEXTURE_IMAGES_PER_LINE;

                return CCRectMake(
                    TEXTURE_SPACING + (TEXTURE_TILE_WIDTH + TEXTURE_SPACING) * ix,
                    TEXTURE_SPACING + (TEXTURE_TILE_HEIGHT + TEXTURE_SPACING) * iy,
                    TEXTURE_TILE_WIDTH,
                    TEXTURE_TILE_HEIGHT
                );
            }

        };
    }
}

#endif