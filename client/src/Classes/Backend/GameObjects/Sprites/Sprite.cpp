
#include <stdio.h>

#include "Sprite.h"
#include "AISprite.h"
#include "../../../Common/Cache/ObjectCache.h"

using namespace Bomber::Backend;
using namespace Bomber::Common;

Sprite *Sprite::getInstanceByGid(unsigned int gid)
{
    AISprite *sprite = (AISprite *) ObjectCache::getInstance()->getObject(COT_AI_SPRITE);
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
        case 453:
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

void Sprite::init()
{
    GameObject::init();

    _attributes->init();
}

Sprite::~Sprite()
{
    delete _attributes;
}
