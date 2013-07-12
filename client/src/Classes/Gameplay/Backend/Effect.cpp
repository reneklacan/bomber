
#include "Effect.h"

using namespace Bomber::Backend;

Effect *Effect::getInstanceByGid(unsigned int gid)
{
    if (gid == 18)
    {
        return new EffectBombPowerInc();
    }
    else if (gid == 13)
    {
        return new EffectBombCapacityInc();
    }

    printf("Effect::getInstanceByGid - unknown effect gid %u\n", gid);
    return NULL;
}