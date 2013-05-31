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
