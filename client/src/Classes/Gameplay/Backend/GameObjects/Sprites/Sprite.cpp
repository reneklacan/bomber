
#include "Sprite.h"
#include "AISprite.h"

using namespace Bomber::Backend;

Sprite *Sprite::getInstanceByGid(unsigned int gid)
{
    AISprite *sprite = new AISprite();
    sprite->setGid(gid);
        
    switch(gid)
    {
        case 2:
            sprite->setName("Timmy");
            break;
        case 3:
            sprite->setName("Amanda");
            break;
        case 4:
            sprite->setName("Sabrina");
            break;
        case 5:
            sprite->setName("July");
            break;
        case 6:
            sprite->setName("Princess");
            break;
        case 48:
            sprite->setName("Fluffy");
            break;
        default:
            printf("Sprite::getInstanceByGid - unknown sprite gid %u\n", gid);
            //printf("Segfault comiiiiiing...\n");
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
