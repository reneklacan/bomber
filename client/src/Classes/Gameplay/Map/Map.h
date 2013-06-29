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
        CC_SYNTHESIZE(CCArray *, _bombs, Bombs);
        //CC_SYNTHESIZE(CCDictionary *, _spawnedBombs, SpawnedBombs);
        CC_SYNTHESIZE(CCDictionary *, _portals, Portals);
        CC_SYNTHESIZE(CCDictionary *, _portalExits, PortalExits);
        CC_SYNTHESIZE(CCTMXTiledMap *, _tiledMap, TiledMap);
        CC_SYNTHESIZE(int*, _obstaclesMap, ObstaclesMap);

        Map();
        ~Map();
        virtual bool init();

        CREATE_FUNC(Map);

        void updateBombs(float dt);
        void spawnBomb(GameSprite *owner);
        void addToPosition(CCPoint point);

        std::map<unsigned int, CCObject*> _spawnedBombs;
        void addBomb(unsigned int key, CCObject* bomb)
        {
            _spawnedBombs[key] = bomb;
        }
        CCObject *getBomb(unsigned int key)
        {
            return _spawnedBombs[key];
        }
        void removeBomb(unsigned int key)
        {
            _spawnedBombs.erase(key);
        }
};

#endif

