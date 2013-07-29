
#include <stdio.h>

#include "Obstacle.h"

#include "../BackendCache.h"

using namespace Bomber::Backend;

Obstacle *Obstacle::getInstanceByGid(unsigned int gid)
{
    Obstacle *obstacle = nullptr;

    switch(gid)
    {
        case 20:
        case 36:
            obstacle = (Obstacle *) BackendCache::getInstance()->getObject(COT_MAZE_BLOCK);
            break;
        case 25:
            obstacle = (Obstacle *) BackendCache::getInstance()->getObject(COT_LEVER_BLOCK);
            break;
        case 41:
        case 42:
            obstacle = (Obstacle *) BackendCache::getInstance()->getObject(COT_DESTROYABLE_BLOCK);
            break;
        case 43:
            obstacle = (Obstacle *) BackendCache::getInstance()->getObject(COT_PUSHABLE_BLOCK);
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
