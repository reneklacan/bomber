
#include <stdio.h>

#include "Obstacle.h"

using namespace Bomber::Backend;

void Obstacle::configureFromGid(unsigned int gid)
{
    _name = "wut";

    if (gid == 20)
    {
        _name = "maze";
        _toughness = -1;
    }
    else if (gid == 42)
    {
        _name = "block";
        _toughness = 1;
    }
    else if (gid == 25)
    {
        _name = "lever";
        _toughness = -1;
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
