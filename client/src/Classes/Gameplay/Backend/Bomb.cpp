
#include "Bomb.h"

using namespace Bomber::Backend;

Bomb::Bomb()
{
    _expired = 0.0f;
    _detonated = false;
    _timeout = 2.0f;
    _penetration = 1;
    _owner = 0;
    _power = 2;
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

void Bomb::configure(GameObject *owner)
{
    // configure bomb by owner's attributes
}

