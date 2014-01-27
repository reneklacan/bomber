
#include <stdio.h>

#include "AdvancedSprite.h"
#include "Mobs/SmartMob.h"
#include "Mobs/ScriptedMob.h"
#include "../../../Common/Cache/ObjectCache.h"

using namespace Bomber::Backend;
using namespace Bomber::Common;

Sprite *Sprite::getInstanceByGid(unsigned int gid)
{
    AdvancedSprite *sprite = (AdvancedSprite *) ObjectCache::getInstance()->getObject(COT_SMART_MOB);
    sprite->setGid(gid);

    switch(gid)
    {
        //case 2:
        case 459:
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
        //case 6:
        case 453:
            sprite->setName("Princess");
            break;
        case 48:
            sprite->setName("Fluffy");
            break;
        case 523:
            //sprite = new ScriptedSprite();
            sprite = (AdvancedSprite *) ObjectCache::getInstance()->getObject(COT_SCRIPTED_MOB);
            sprite->setName("Geisha");
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
