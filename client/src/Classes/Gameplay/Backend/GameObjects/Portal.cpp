
#include <stdio.h>

#include "Portal.h"

using namespace Bomber::Backend;

Portal::Portal() : GameObject()
{
    _name = "portal";
}

void Portal::configure(int top, int bottom, int left, int right)
{
    _topTarget = top;
    _bottomTarget = bottom;
    _leftTarget = left;
    _rightTarget = right;
}

int Portal::getPortalTarget(Coordinates coords)
{
    Coordinates portalCoords = this->getCoords();

    if (coords.x < portalCoords.x)
        return _leftTarget;

    if (coords.x > portalCoords.x)
        return _rightTarget;

    if (coords.y < portalCoords.y)
        return _bottomTarget;

    if (coords.y > portalCoords.y)
        return _topTarget;

    printf("Portal::getPortalTarget - same coords as portalCoords? hm?\n");
    return -1;
}
