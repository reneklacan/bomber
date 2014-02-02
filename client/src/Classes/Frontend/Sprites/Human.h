#ifndef __BOMBER_HUMAN
#define __BOMBER_HUMAN

#include "cocos2d.h"
#include "ActionSprite.h"
#include "../Map/Map.h"
#include "../../Input/ActionDelegates.h"
#include <string>

using namespace cocos2d;

class Human : public ActionSprite, public GameActionDelegate
{
    public:
        Human(Texture2D *texture, Rect defaultImage);

        virtual void actionOne();
        void actionTwo();
        void actionThree();
        void plantBomb();

    private:
};

#endif
