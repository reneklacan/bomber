
#include "Effect.h"

using namespace Bomber::Backend;

Effect *Effect::getInstanceByGid(unsigned int gid)
{
    Effect *effect = nullptr;
    
    switch(gid)
    {
        case 13:
            effect = new EffectBombCapacityInc();
            break;
        case 18:
            effect = new EffectSpeedInc();
            break;
        case 46:
            effect = new EffectBombPowerInc();
            break;
        default:
            printf("Effect::getInstanceByGid - unknown effect gid %u\n", gid);
            printf("Segfault comiiiiiing...\n");
    }

    effect->setGid(gid);

    return effect;
}