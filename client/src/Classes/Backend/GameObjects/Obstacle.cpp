
#include <stdio.h>

#include "Obstacle.h"

#include "../../Common/Cache/ObjectCache.h"

using namespace Bomber::Backend;
using namespace Bomber::Common;

Obstacle *Obstacle::getInstanceByGid(unsigned int gid)
{
    Obstacle *obstacle = nullptr;

    switch(gid)
    {
        //case 20:
        //case 36:
        case 151:
        case 273:
            obstacle = (Obstacle *) ObjectCache::getInstance()->getObject(COT_MAZE_BLOCK);
            break;
        case 25:
            obstacle = (Obstacle *) ObjectCache::getInstance()->getObject(COT_LEVER_BLOCK);
            break;
        //case 41:
        //case 42:
        case 276:
            obstacle = (Obstacle *) ObjectCache::getInstance()->getObject(COT_DESTROYABLE_BLOCK);
            break;
        //case 43:
        case 258:
            obstacle = (Obstacle *) ObjectCache::getInstance()->getObject(COT_PUSHABLE_BLOCK);
            break;
        default:
            printf("Obstacle::getInstanceByGid - unknown obstacle gid %u\n", gid);
            printf("Segfault comiiiiiing...\n");
    }

    obstacle->setGid(gid);

    return obstacle;
}

Obstacle::Obstacle()
:GameObject()
,_pushable(false)
{
    this->init();
}

int Obstacle::decreaseToughness()
{
    _toughness -= 1;
    return _toughness;
}

int Obstacle::decreaseToughness(int amount)
{
    _toughness -= amount;
    return _toughness;
}
