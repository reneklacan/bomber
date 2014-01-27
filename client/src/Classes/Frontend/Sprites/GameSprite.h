#ifndef __BOMBER_GAME_SPRITE
#define __BOMBER_GAME_SPRITE

// AKTUALNE SA NEVYUZIVA

#include "cocos2d.h"

using namespace cocos2d;

class GameSprite : public Sprite
{
    public:

        GameSprite();
        //~GameSprite();
        static GameSprite* gameSpriteWithFile(const char * pszFileName);

        virtual Rect getCollisionBox(Point point);
        virtual Rect getCollisionBox();
        virtual void actionOne();
        virtual const char* spriteName();
        virtual void logInfo();
        virtual Point getTilemapPosition();

    protected:
        CC_SYNTHESIZE(int, _speed, Speed);
        CC_SYNTHESIZE(Point, _nextPosition, NextPosition);
        CC_SYNTHESIZE(Point, _nextPositionDelta, NextPositionDelta);
        CC_SYNTHESIZE(unsigned int, _id, ID);
        CC_SYNTHESIZE(bool, _isAlive, IsAlive);

    private:
};

#endif
