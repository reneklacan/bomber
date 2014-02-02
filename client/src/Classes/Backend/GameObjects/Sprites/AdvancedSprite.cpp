
#include "AdvancedSprite.h"

using namespace Bomber::Backend;

AdvancedSprite::AdvancedSprite()
:AdvancedAI()
{

}

void AdvancedSprite::init()
{
    AdvancedAI::init();

    _attributes->init();
}
