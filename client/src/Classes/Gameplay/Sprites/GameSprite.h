#ifndef __BOMBER_GAME_SPRITE
#define __BOMBER_GAME_SPRITE

#include "cocos2d.h"

using namespace cocos2d;

class GameSprite : public CCSprite
{
    public:
        CC_SYNTHESIZE(float, _speed, Speed);
        CC_SYNTHESIZE(CCPoint, _nextPosition, NextPosition);
        CC_SYNTHESIZE(CCPoint, _nextPositionDelta, NextPositionDelta);

        GameSprite();
        //~GameSprite();
        static GameSprite* gameSpriteWithFile(const char * pszFileName);

        virtual CCRect getCollisionBox(CCPoint point);
        virtual CCRect getCollisionBox();
        virtual void actionOne();
        virtual const char* spriteName();
        virtual void logInfo();
        virtual CCPoint getTilemapPosition();

        virtual void setID(unsigned int id) { _id = id; }
        virtual unsigned int getID() { return _id; }

    protected:
        unsigned int _id;

    private:
};

#endif
