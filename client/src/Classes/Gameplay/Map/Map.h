#ifndef __BOMBER_MAP
#define __BOMBER_MAP

#include "cocos2d.h"
#include "../Sprites/GameSprite.h"
#include <map>

using namespace cocos2d;

class Map : public CCLayer
{
    public:
        CC_SYNTHESIZE(int, _width, Width);
        CC_SYNTHESIZE(int, _height, Height);
        CC_SYNTHESIZE(CCDictionary *, _portals, Portals);
        CC_SYNTHESIZE(CCTMXTiledMap *, _tiledMap, TiledMap);
        std::map<unsigned int, CCObject*> _spawnedBombs;

        Map();
        ~Map();
        virtual bool init();
        CREATE_FUNC(Map);
        
        void addToPosition(CCPoint point);

        void addBomb(unsigned int key, CCObject* bomb);
        CCObject *getBomb(unsigned int key);
        void removeBomb(unsigned int key);
};

#endif

