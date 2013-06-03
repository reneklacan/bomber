#ifndef __BOMBER_MAP
#define __BOMBER_MAP

#include "cocos2d.h"
#include "../Sprites/GameSprite.h"

using namespace cocos2d;

class Map : public CCLayer
{
    public:
        Map();

        void update(float dt);
        void spawnBomb(GameSprite *owner);

    private:
        CCArray *_bombs;
};


#endif

