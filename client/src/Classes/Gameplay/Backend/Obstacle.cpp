
#include <stdio.h>

#include "Obstacle.h"

using namespace Bomber::Backend;

void Obstacle::configureFromGid(unsigned int gid)
{
    if (gid == 20)
    {
        this->setToughness(0);
    }
    else if (gid == 42)
    {
        this->setToughness(1);
    }
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
