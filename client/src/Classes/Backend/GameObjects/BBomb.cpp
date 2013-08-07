
#include <stdio.h>

#include "BBomb.h"
#include "../../Constants.h"

using namespace Bomber::Backend;
using namespace Bomber::Common;

Bomb::Bomb() : GameObject()
{
    this->init();
}

void Bomb::init()
{
    GameObject::init();

    _expired = 0.0f;
    _detonated = false;
    _ownerId = 0;
}

void Bomb::update(float dt)
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

void Bomb::configure(Sprite *owner)
{
    // configure bomb by owner's attributes

    _ownerId = owner->getId();
    _power = owner->getAttributes()->getBombPower();
    _timeout = owner->getAttributes()->getBombTimeout();
    _penetration = owner->getAttributes()->getBombPenetration();
    _damage = owner->getAttributes()->getBombDamage();

    Coordinates coords = owner->getCoords();

    this->setPosition(
            coords.x*TILE_WIDTH + TILE_WIDTH/2,
            coords.y*TILE_HEIGHT + TILE_HEIGHT/2
    );
}

