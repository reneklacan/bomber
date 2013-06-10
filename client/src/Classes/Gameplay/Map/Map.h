#ifndef __BOMBER_MAP
#define __BOMBER_MAP

#include "cocos2d.h"
#include "../Sprites/GameSprite.h"

using namespace cocos2d;

class Map : public CCLayer
{
    public:
        CC_SYNTHESIZE(CCArray *, _bombs, Bombs);
        CC_SYNTHESIZE(CCDictionary *, _portals, Portals);
        CC_SYNTHESIZE(CCDictionary *, _portalExits, PortalExits);
        CC_SYNTHESIZE(CCTMXTiledMap *, _tiledMap, TiledMap);

        Map();
        ~Map();
        virtual bool init();

        CREATE_FUNC(Map);

        void update(float dt);
        void spawnBomb(GameSprite *owner);
};


#endif

