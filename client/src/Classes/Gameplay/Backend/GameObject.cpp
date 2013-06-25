
#include "GameObject.h"
#include "../../Constants.h"

using namespace Bomber::Backend;

void GameObject::setPosition(int x, int y)
{
    _position = Position(x, y);
}

void GameObject::setPosition(Position position)
{
    _position = position;
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
    Coordinates coords;
    coords.x = _position.x/TILE_WIDTH;
    coords.y = _position.y/TILE_HEIGHT;
    return coords;
}

/*
Coordinates GameObject::getNextCoords()
{
    Coordinates coords;
    return coords;
}
*/
