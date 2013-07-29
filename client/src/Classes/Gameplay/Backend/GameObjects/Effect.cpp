
#include "Effect.h"

#include "../BackendCache.h"

using namespace Bomber::Backend;

Effect *Effect::getInstanceByGid(unsigned int gid)
{
    Effect *effect = nullptr;
    
    switch(gid)
    {
        case 13:
            effect = (Effect *) BackendCache::getInstance()->getObject(COT_BOMB_CAPACITY_INC);
            break;
        case 18:
            effect = (Effect *) BackendCache::getInstance()->getObject(COT_SPEED_INC);
            break;
        case 46:
            effect = (Effect *) BackendCache::getInstance()->getObject(COT_BOMB_POWER_INC);
            break;
        default:
            printf("Effect::getInstanceByGid - unknown effect gid %u\n", gid);
            printf("Segfault comiiiiiing...\n");
    }

    effect->setGid(gid);

    return effect;
}