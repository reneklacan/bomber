
#include "Effect.h"
#include "Sprites/AdvancedSprite.h"

#include "../../Common/Cache/ObjectCache.h"
#include "../../Common/Utils.h"

using namespace Bomber::Backend;
using namespace Bomber::Common;

Effect *Effect::getInstanceByGid(unsigned int gid)
{
    Effect *effect = nullptr;

    //gid = convertGidToOld(gid);

    switch(convertGidToOld(gid))
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
        case 264: // cage
            effect = (Effect *) ObjectCache::getInstance()->getObject(COT_LEVEL_KEY);
            break;
        case 639:
        case 1809: // red boots
            effect = (Effect *) ObjectCache::getInstance()->getObject(COT_FIRE_IMMUNITY);
            break;
        case 638:
        case 1810: // red boots
            effect = (Effect *) ObjectCache::getInstance()->getObject(COT_WATER_IMMUNITY);
            break;
        case 387:
            effect = (Effect *) ObjectCache::getInstance()->getObject(COT_FIRE_TRAP);
            break;
        case 360:
            effect = (Effect *) ObjectCache::getInstance()->getObject(COT_WATER_TRAP);
            break;
        case 603:
        case 736: // portal icon :-/
            effect = (Effect *) ObjectCache::getInstance()->getObject(COT_CLEAR_IMMUNITIES);
            break;
        case 369: // hole in the floor
            effect = (Effect *) ObjectCache::getInstance()->getObject(COT_DEATH);
            break;
        case 1729: // gray shield
            effect = (Effect *) ObjectCache::getInstance()->getObject(COT_FOG_ON);
            break;
        case 434: // shift up
            effect = (Effect *) ObjectCache::getInstance()->getObject(COT_SHIFT_UP);
            break;
        case 433: // shift down
        case 435: // shift left
        case 436: // shift right
            effect = (Effect *) ObjectCache::getInstance()->getObject(COT_NO_EFFECT); // tmp
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

bool EffectDeath::applyToSprite(Sprite *sprite)
{
    sprite->getAttributes()->decreaseHealth(9999);
    return false;
}
