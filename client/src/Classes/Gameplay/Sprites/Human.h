#ifndef __BOMBER_HUMAN
#define __BOMBER_HUMAN

#include "cocos2d.h"
#include "GameSprite.h"
#include "../Map/Map.h"

using namespace cocos2d;

class Human : public GameSprite
{
    public:
        CC_SYNTHESIZE(Map *, _map, Map);

        Human();
        //~Human();

        static Human* create(Map *map);

        virtual void actionOne();
        void plantBomb();
};

#endif
