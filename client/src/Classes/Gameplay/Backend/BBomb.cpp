
#include <stdio.h>

#include "BBomb.h"
#include "../../Constants.h"

using namespace Bomber::Backend;

BBomb::BBomb()
{
    _expired = 0.0f;
    _detonated = false;
    _timeout = 2.0f;
    _penetration = 1;
    _ownerId = 0;
    _power = 2;
    _damage = 70;
}

void BBomb::update(float dt)
{
    if (_detonated)
    {
        return;
    }

    _expired += dt;

    if (_expired >= _timeout)
    {
        _detonated = true;
    }
}

void BBomb::configure(GameObject *owner)
{
    // configure bomb by owner's attributes

    Coordinates coords = owner->getCoords();

    this->setPosition(
            coords.x*TILE_WIDTH + TILE_WIDTH/2,
            coords.y*TILE_HEIGHT + TILE_HEIGHT/2
    );
}

