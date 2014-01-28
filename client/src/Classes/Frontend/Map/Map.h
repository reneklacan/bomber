#ifndef __BOMBER_MAP
#define __BOMBER_MAP

#include "cocos2d.h"
#include <map>

using namespace cocos2d;

class Map : public Layer
{
    public:
        Map(){};
        ~Map(){};

        virtual bool init();
        CREATE_FUNC(Map);
        void addToPosition(Point point);

    private:
        CC_SYNTHESIZE(int, _width, Width);
        CC_SYNTHESIZE(int, _height, Height);
        CC_SYNTHESIZE(TMXTiledMap *, _tiledMap, TiledMap);
};

#endif

