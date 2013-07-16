#include "SpriteCreator.h"

using namespace Bomber::Frontend;

//
SpriteCreator *SpriteCreator::getInstance()
{
    static SpriteCreator instance;
    return &instance;
}

//
Sprite* SpriteCreator::createObstacle()
{
	return NULL;
}

//
Sprite* SpriteCreator::createSprite()
{
	return NULL;
}

//
Sprite* SpriteCreator::createEffect(Texture2D *texture, Rect rect)
{
	Sprite *effect = Sprite::createWithTexture(
        texture,
        rect 
    );
    effect->setAnchorPoint( ccp(0, 0) );
    effect->setVertexZ(0);
    return effect;
}

//
Sprite* SpriteCreator::createBomb()
{
	return NULL;
}