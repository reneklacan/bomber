
#include <stdio.h>

#include "Sprite.h"
#include "AISprite.h"
#include "../../BackendCache.h"

using namespace Bomber::Backend;

Sprite *Sprite::getInstanceByGid(unsigned int gid)
{
    AISprite *sprite = (AISprite *) BackendCache::getInstance()->getObject(COT_AI_SPRITE);
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
:GameObject()
,_attributes(new SpriteAttributes())
{
    _name = "sprite?";
}

Sprite::~Sprite()
{
    delete _attributes;
}
