
#include <stdio.h>

#include "Obstacle.h"

using namespace Bomber::Backend;

Obstacle *Obstacle::getInstanceByGid(unsigned int gid)
{
    Obstacle *obstacle = nullptr;

    switch(gid)
    {
        case 20:
            obstacle = new MazeBlock();
            break;
        case 25:
            obstacle = new LeverBlock();
            break;
        case 42:
            obstacle = new DestroyableBlock();
            break;
        case 43:
            obstacle = new PushableBlock();
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
