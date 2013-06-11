#include "GameSprite.h"
#include "../../Constants.h"

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
    return this->getCollisionBox(_nextPosition);
}

CCRect GameSprite::getCollisionBox(CCPoint point)
{
    return CCRectMake(
            point.x - (this->getContentSize().width/2), // aww, division in every frame? :(
            point.y - (this->getContentSize().height/2),
            this->getContentSize().width,
            this->getContentSize().height/4
    );
}

CCPoint GameSprite::getTilemapPosition()
{
    CCPoint pos = this->getPosition();
    CCSize size = this->getContentSize();

    return ccp( 
        (pos.x - size.width/2 + 35.5f)/TILE_WIDTH,
        (pos.y - size.height/2 + 95.5f - TILE_HEIGHT)/TILE_HEIGHT
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
