
#include "Effect.h"
#include "Sprites/AdvancedSprite.h"

#include "../../Common/Cache/ObjectCache.h"

using namespace Bomber::Backend;
using namespace Bomber::Common;

Effect *Effect::getInstanceByGid(unsigned int gid)
{
    Effect *effect = nullptr;

    switch(gid)
    {
        case 13:
            effect = (Effect *) ObjectCache::getInstance()->getObject(COT_BOMB_CAPACITY_INC);
            break;
        case 604:
            effect = (Effect *) ObjectCache::getInstance()->getObject(COT_SPEED_INC);
            break;
        case 607:
            effect = (Effect *) ObjectCache::getInstance()->getObject(COT_BOMB_POWER_INC);
            break;
        case 623:
            effect = (Effect *) ObjectCache::getInstance()->getObject(COT_LEVEL_KEY);
            break;
        case 639:
            effect = (Effect *) ObjectCache::getInstance()->getObject(COT_FIRE_IMMUNITY);
            break;
        case 638:
            effect = (Effect *) ObjectCache::getInstance()->getObject(COT_WATER_IMMUNITY);
            break;
        case 387:
            effect = (Effect *) ObjectCache::getInstance()->getObject(COT_FIRE_TRAP);
            break;
        case 360:
            effect = (Effect *) ObjectCache::getInstance()->getObject(COT_WATER_TRAP);
            break;
        case 603:
            effect = (Effect *) ObjectCache::getInstance()->getObject(COT_CLEAR_IMMUNITIES);
            break;
        case 434:
            effect = (Effect *) ObjectCache::getInstance()->getObject(COT_SHIFT_UP);
            break;

        default:
            printf("Effect::getInstanceByGid - unknown effect gid %u\n", gid);
            printf("Segfault comiiiiiing...\n");
    }

    effect->setGid(gid);

    return effect;
}

bool EffectShiftUp::applyToSprite(Sprite *sprite)
{
    if (!sprite->isAdvanced())
        return false;

    auto advancedSprite = (AdvancedSprite *) sprite;

    if (advancedSprite->isInControl())
        return false;

    advancedSprite->runAction(new GoUp(1));

    return false;
}
