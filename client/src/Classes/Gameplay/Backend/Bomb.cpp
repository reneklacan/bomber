
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
    _activated = false;
}

void Bomb::update(float dt)
{
    if (!_activated || _detonated)
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

void Bomb::activate()
{
    _activated = true;

    GSCBombSpawn *change = new GSCBombSpawn();
    change->update(this->getPosition());
    _eventDelegate->notify(change);
}

