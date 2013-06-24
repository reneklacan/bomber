
#include "GameObject.h"

using namespace Bomber::Backend;

void GameObject::setPosition(Position position)
{
    _position = position;

    _eventDelegate->update(new GameStateChange());
}

Coordinates GameObject::getCoords()
{
    Coordinates coords;
    return coords;
}

Coordinates GameObject::getNextCoords()
{
    Coordinates coords;
    return coords;
}

void GameObject::setEventDelegate(GameObjectEventDelegate* delegate)
{
    _eventDelegate = delegate;
}
