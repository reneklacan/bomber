#ifndef __BOMBER_GAME_SPRITE
#define __BOMBER_GAME_SPRITE

#include "cocos2d.h"

using namespace cocos2d;

class GameSprite : public Sprite
{
    public:
        CC_SYNTHESIZE(float, _speed, Speed);
        CC_SYNTHESIZE(Point, _nextPosition, NextPosition);
        CC_SYNTHESIZE(Point, _nextPositionDelta, NextPositionDelta);

        GameSprite();
        //~GameSprite();
        static GameSprite* gameSpriteWithFile(const char * pszFileName);

        virtual Rect getCollisionBox(Point point);
        virtual Rect getCollisionBox();
        virtual void actionOne();
        virtual const char* spriteName();
        virtual void logInfo();
        virtual Point getTilemapPosition();

        virtual void setID(unsigned int id) { _id = id; }
        virtual unsigned int getID() { return _id; }

    protected:
        unsigned int _id;

    private:
};

#endif
