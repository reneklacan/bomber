#ifndef __BOMBER_MAP
#define __BOMBER_MAP

#include "cocos2d.h"
#include "../Sprites/GameSprite.h"
#include <map>

using namespace cocos2d;

class Map : public Layer
{
    public:
        CC_SYNTHESIZE(int, _width, Width);
        CC_SYNTHESIZE(int, _height, Height);
        CC_SYNTHESIZE(Dictionary *, _portals, Portals);
        CC_SYNTHESIZE(TMXTiledMap *, _tiledMap, TiledMap);
        std::map<unsigned int, Object*> _spawnedBombs;

        Map();
        ~Map();
        virtual bool init();
        CREATE_FUNC(Map);
        
        void addToPosition(Point point);

        void reset();

        void addBomb(unsigned int key, Object* bomb);
        Object *getBomb(unsigned int key);
        void removeBomb(unsigned int key);
};

#endif

