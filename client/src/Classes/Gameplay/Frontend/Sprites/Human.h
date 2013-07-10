#ifndef __BOMBER_HUMAN
#define __BOMBER_HUMAN

#include "cocos2d.h"
#include "GameSprite.h"
#include "../Map/Map.h"
#include "../../../Input/ActionDelegates.h"
#include <string>

using namespace cocos2d;

class Human : public GameSprite, public GameActionDelegate
{
    public:
        CC_SYNTHESIZE(Map *, _map, Map);

        Human();
        //~Human();

        static Human* create(Map *map, int type);

        virtual void actionOne();
        void actionTwo();
        void actionThree();
        void plantBomb();

    private:
};

#endif
