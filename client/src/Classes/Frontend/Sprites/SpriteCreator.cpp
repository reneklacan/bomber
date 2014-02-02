#include "SpriteCreator.h"

using namespace Bomber::Frontend;

//
SpriteCreator *SpriteCreator::getInstance()
{
    static SpriteCreator instance;
    return &instance;
}

//
Sprite* SpriteCreator::createObstacle(Texture2D *texture, Rect rect)
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
ActionSprite* SpriteCreator::createSprite(Texture2D *texture, Rect rect)
{
	ActionSprite *effect = new ActionSprite(
        texture,
        rect 
    );
    effect->setAnchorPoint( ccp(0, 0) );
    effect->setVertexZ(0);
    return effect;
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
Sprite* SpriteCreator::createBomb(Texture2D *texture, Rect rect)
{
	Sprite *effect = Sprite::createWithTexture(
        texture,
        rect 
    );
    effect->setAnchorPoint( ccp(0.5, 0.35) );
    effect->setVertexZ(0);
    return effect;
}