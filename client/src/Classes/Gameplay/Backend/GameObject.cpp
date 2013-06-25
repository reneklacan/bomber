
#include "GameObject.h"

using namespace Bomber::Backend;

void GameObject::moveToPosition(Position position)
{
    GSCSpriteMove *change = new GSCSpriteMove();
    change->update(_position, position);
    change->setGameObjectId(this->getId());
    _eventDelegate->notify(change);
    _position = position;
}

void GameObject::overridePosition(Position position)
{
    GSCSpritePositionOverride *change = new GSCSpritePositionOverride();
    change->update(position);
    change->setGameObjectId(this->getId());
    _eventDelegate->notify(change);
    _position = position;
}

void GameObject::setPosition(Position position)
{

}

void GameObject::setNextPosition(Position position)
{

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
