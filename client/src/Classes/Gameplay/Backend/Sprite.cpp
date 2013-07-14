
#include "Sprite.h"
#include "AISprite.h"

using namespace Bomber::Backend;

Sprite *Sprite::getInstanceByGid(unsigned int gid)
{
    AISprite *sprite = new AISprite();
    sprite->setGid(gid);

    if (gid == 2)
    {
        sprite->setName("Timmy");
    }
    else if (gid == 3)
    {
        sprite->setName("Amanda");
    }
    else if (gid == 4)
    {
        sprite->setName("Sabrina");
    }
    else if (gid == 5)
    {
        sprite->setName("July");
    }
    else if (gid == 6)
    {
        sprite->setName("Princess");
    }
    else if (gid == 48)
    {
        sprite->setName("Fluffy");
    }

    return sprite;
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
