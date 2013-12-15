
#include <math.h>

#include "Movement.h"
#include "../../Constants.h"

using namespace Bomber::Backend;
using namespace Bomber::Common;

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
,_direction(direction)
,_speed(speed)
{
    _object->setInMovement(true);

    _goal = Position(
        _start.x + (goalCoords.x - _object->getCoords().x)*TILE_WIDTH,
        _start.y + (goalCoords.y - _object->getCoords().y)*TILE_HEIGHT
    );
}

void Movement::update(float dt)
{
    if (_finished)
        return;

    float step = _speed*dt;
    _current = _current.getNext(step, _direction);
    _object->setPosition(_current);

    //printf("Movement::Movement _current pos x=%g, y=%g\n", _current.x, _current.y);

    Position delta = _goal - _current;

    if (((_direction == UP || _direction == DOWN) && fabs(delta.y) < 2*step) || ((_direction == LEFT || _direction == RIGHT) && fabs(delta.x) < 2*step))
    {
        //_object->setPosition(_goal);
        _object->setInMovement(false);
        _finished = true;
    }
}
