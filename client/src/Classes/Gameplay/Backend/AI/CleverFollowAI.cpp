
#include "CleverFollowAI.h"
#include "AI.h"
#include "../../../Constants.h"

using namespace Bomber::Backend;

CleverFollowAI::CleverFollowAI()
: Sprite()
{
    _state = STATE_NONE;
    _aggroDistance = -1.0;
}

void CleverFollowAI::update(float dt)
{
    // TODO in movement respect player's attributes like speed
    //      this->getAttributes()->getSpeed();

    Coordinates goalCoords;
    Position delta;
    Position nextPos = _position;
    std::deque<Coordinates> path;

    switch (_state)
    {
        case STATE_NONE:
            path = AI::getInstance()->findPathToNearestPlayer(this->getCoords(), _aggroDistance);
            
            if (path.size() != 0)
            {
                goalCoords = path[0];
            }
            else
            {
                goalCoords = AI::getInstance()->getRandomCoordsAround(this->getCoords());
            }

            _goal = Position(goalCoords.x*TILE_WIDTH, goalCoords.y*TILE_HEIGHT);
            _state = STATE_MOVING;
            //break;

        case STATE_MOVING:
            delta = _goal - _position;

            if (delta.x > TILE_WIDTH + 1 || delta.y > TILE_HEIGHT + 1)
            {
                _state = STATE_NONE;
            }
            else if (delta < 2.0f && delta > -0.2f)
            {
                _state = STATE_NONE;
            }
            else
            {
                if (fabs(delta.x) > fabs(delta.y))
                {
                    if (delta.x > 0.5)
                    {
                        nextPos.x = _position.x + 1.0f;
                    }
                    else if (delta.x < 0.5)
                    {
                        nextPos.x = _position.x - 1.0f;
                    }
                }
                else
                {
                    if (delta.y > 0.5)
                    {
                        nextPos.y = _position.y + 1.0f;
                    }
                    else if (delta.y < 0.5)
                    {
                        nextPos.y = _position.y - 1.0f;
                    }
                }
                this->setPosition(nextPos);
            }
            break;
    }
}
