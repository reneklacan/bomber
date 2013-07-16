
#include "Effect.h"

using namespace Bomber::Backend;

Effect *Effect::getInstanceByGid(unsigned int gid)
{
    Effect *effect = nullptr;

    if (gid == 18)
    {
        effect = new EffectSpeedInc();
    }
    else if (gid == 13)
    {
        effect = new EffectBombCapacityInc();
    }
    else if (gid == 46)
    {
        effect = new EffectBombPowerInc();
    }
    else
    {
        printf("Effect::getInstanceByGid - unknown effect gid %u\n", gid);
        printf("Segfault comiiiiiing...\n");
    }

    effect->setGid(gid);

    return effect;
}