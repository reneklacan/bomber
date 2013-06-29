
#include <stdio.h>

#include "GameObject.h"
#include "../../Constants.h"

using namespace Bomber::Backend;

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

/*
void GameObject::setNextPosition(Position position)
{

}
*/

Coordinates GameObject::getCoords()
{
    return Coordinates(
            _position.x/TILE_WIDTH,
            _position.y/TILE_HEIGHT
    );
}

/*
Coordinates GameObject::getNextCoords()
{
    Coordinates coords;
    return coords;
}
*/
