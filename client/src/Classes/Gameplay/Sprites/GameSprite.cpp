#include "GameSprite.h"

GameSprite::GameSprite()
:_speed(10.0f)
{

}

/*
GameSprite::~GameSprite()
{

}

bool GameSprite::init()
{
    if (!CCSprite::init())
        return false;

    return true;
}
*/

GameSprite* GameSprite::gameSpriteWithFile(const char * pszFileName)
{
    GameSprite * sprite = new GameSprite();

    if (sprite && sprite->initWithFile(pszFileName))
    {
        sprite->autorelease();
        return sprite;
    }

    CC_SAFE_DELETE(sprite);
    return NULL;
}

CCRect GameSprite::getCollisionBox()
{
    return CCRectMake(
            _nextPosition.x - (this->getContentSize().width/4),
            _nextPosition.y - (this->getContentSize().height/2),
            this->getContentSize().width/2,
            this->getContentSize().height/1.5
    );
}

void GameSprite::actionOne()
{

}

const char *GameSprite::spriteName()
{
    return "GameSprite";
}

void GameSprite::logInfo()
{
    CCLog(
            "++++++++Sprite width:%f, height:%f",
            this->getContentSize().width,
            this->getContentSize().height
    );
    CCLog(
            "++++++++Sprite x:%f, y:%f",
            this->getPosition().x,
            this->getPosition().y
    );
}
