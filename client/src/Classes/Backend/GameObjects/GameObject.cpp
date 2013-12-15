
#include <stdio.h>

#include "GameObject.h"
#include "../../Constants.h"

using namespace Bomber::Backend;
using namespace Bomber::Common;

GameObject::GameObject()
:_active(true)
,_inMovement(false)
,_madeCoordsAction(false)
,_dirty(false)
,_circleCollider(false)
,_id(0)
,_gid(0)
{

}

void GameObject::init()
{
    _active = true;
    _inMovement = false;
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
        _madeCoordsAction = false;
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

