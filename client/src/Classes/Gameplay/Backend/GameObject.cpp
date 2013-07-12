
#include <stdio.h>

#include "GameObject.h"
#include "../../Constants.h"

using namespace Bomber::Backend;

GameObject::GameObject()
{
    _circleCollider = false;
}

void GameObject::setPosition(int x, int y)
{
    _position = Position(x, y);
    _dirty = true;
}

void GameObject::setPosition(Position position)
{
    _position = position;
    _dirty = true;
}

void GameObject::setSize(int width, int height)
{
    _size = Size(width, height);
}

void GameObject::setSize(Size size)
{
    _size = size;
}

Coordinates GameObject::getCoords()
{
    Position center = this->getCollisionRect().getCenterPosition();

    Coordinates currentCoords = Coordinates(
            center.x/TILE_WIDTH,
            center.y/TILE_HEIGHT
    );

    if (currentCoords != _currentCoords)
    {
        _previousCoords = _currentCoords;
        _currentCoords = currentCoords;
    }

    return currentCoords;
}

bool GameObject::collides(GameObject *object)
{
    if (!_circleCollider && !object->hasCircleCollider())
    {
        return this->getCollisionRect().isIntersecting(object->getCollisionRect());
    }
    else
    {
        printf("TODO implement circle X rect, circle X circle - %s X %s\n", _name, object->getName());
    }
    return false;
}

