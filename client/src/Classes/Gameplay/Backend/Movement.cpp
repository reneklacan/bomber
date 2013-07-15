
#include "Primitives\Coordinates.h"
#include "Movement.h"
#include "../../Constants.h"

using namespace Bomber::Backend;

Movement::Movement(GameObject *object, Position goal, int direction, int speed)
:_finished(false)
,_object(object)
,_start(object->getPosition())
,_current(_start)
,_goal(goal)
,_direction(direction)
,_speed(speed)
{

}

Movement::Movement(GameObject *object, Coordinates goalCoords, int direction, int speed)
:_finished(false)
,_object(object)
,_start(object->getPosition())
,_current(_start)
,_goal(Position(goalCoords.x*TILE_WIDTH, goalCoords.y*TILE_HEIGHT))
,_direction(direction)
,_speed(speed)
{

}

void Movement::update(float dt)
{
    if (_finished)
        return;

    float step = _speed*dt;
    _current = _current.getNext(step, _direction);
    _object->setPosition(_current);

    Position delta = _goal - _current;

    if (delta < 2*step && delta > -2*step)
    {
        _object->setPosition(_goal);
        _finished = true;
    }
}