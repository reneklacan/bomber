
#include "Effect.h"

using namespace Bomber::Backend;

Effect *Effect::getInstanceByGid(unsigned int gid)
{
    if (gid == 18)
    {
        return new EffectBombPowerInc();
    }

    printf("Effect::getInstanceByGid - unknown effect gid %u\n", gid);
    return NULL;
}