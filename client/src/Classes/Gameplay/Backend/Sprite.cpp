
#include "Sprite.h"
#include "AISprite.h"

using namespace Bomber::Backend;

Sprite *Sprite::getInstanceByGid(unsigned int gid)
{
    return new AISprite();
}

Sprite::Sprite()
: GameObject()
{
    _name = "sprite?";
    _attributes = new SpriteAttributes();
}

Sprite::~Sprite()
{
    delete _attributes;
}
