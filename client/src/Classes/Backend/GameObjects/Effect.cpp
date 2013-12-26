
#include "Effect.h"

#include "../../Common/Cache/ObjectCache.h"

using namespace Bomber::Backend;
using namespace Bomber::Common;

Effect *Effect::getInstanceByGid(unsigned int gid)
{
    Effect *effect = nullptr;
    
    switch(gid)
    {
        case 84: // bullshit
        case 13:
            effect = (Effect *) ObjectCache::getInstance()->getObject(COT_BOMB_CAPACITY_INC);
            break;
        //case 18:
        case 604:
            effect = (Effect *) ObjectCache::getInstance()->getObject(COT_SPEED_INC);
            break;
        //case 46:
        case 607:
            effect = (Effect *) ObjectCache::getInstance()->getObject(COT_BOMB_POWER_INC);
            break;
        case 623:
            effect = (Effect *) ObjectCache::getInstance()->getObject(COT_LEVEL_KEY);
            break;
        default:
            printf("Effect::getInstanceByGid - unknown effect gid %u\n", gid);
            printf("Segfault comiiiiiing...\n");
    }

    effect->setGid(gid);

    return effect;
}
