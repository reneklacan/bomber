
#include "FollowAI.h"
#include "AI.h"
#include "../../../Constants.h"

using namespace Bomber::Backend;
using namespace Bomber::Common;

FollowAI::FollowAI()
: Sprite()
, _state(STATE_NONE)
, _aggroDistance(-1.0)
, _smart(true)
{

}

void FollowAI::update(float dt)
{
    float step;
    Coordinates goalCoords;
    Position delta;
    Position nextPos = _position;
    std::deque<Coordinates> path;

    switch (_state)
    {
        case STATE_NONE:
            path = AI::getInstance()->findPathToNearestPlayer(
                    this->getCoords(),
                    _aggroDistance,
                    _smart,
                    _attributes->getGhostMode()
            );
            
            if (path.size() != 0)
            {
                goalCoords = path[0];
            }
            else
            {
                goalCoords = AI::getInstance()->getRandomCoordsAround(
                        this->getCoords(),
                        _attributes->getGhostMode()
                );
            }

            if (this->getCoords() == goalCoords)
                break;

            _goal = Position(goalCoords.x*TILE_WIDTH, goalCoords.y*TILE_HEIGHT);
            _state = STATE_MOVING;
            //break;

        case STATE_MOVING:
            delta = _goal - _position;
            step = _attributes->getSpeed() * dt;

            if (delta.x > TILE_WIDTH + 2*step || delta.y > TILE_HEIGHT + 2*step)
            {
                _state = STATE_NONE;
            }
            else if (delta < 2*step && delta > -2*step)
            {
                _state = STATE_NONE;
            }
            else
            {
                if (fabs(delta.x) > fabs(delta.y))
                {
                    if (delta.x > 0.5)
                    {
                        nextPos.x = _position.x + step;
                    }
                    else if (delta.x < 0.5)
                    {
                        nextPos.x = _position.x - step;
                    }
                }
                else
                {
                    if (delta.y > 0.5)
                    {
                        nextPos.y = _position.y + step;
                    }
                    else if (delta.y < 0.5)
                    {
                        nextPos.y = _position.y - step;
                    }
                }
                this->setPosition(nextPos);
            }
            break;
    }
}
