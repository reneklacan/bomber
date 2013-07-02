
#include "RandomAI.h"
#include "AI.h"
#include "../../../Constants.h"

using namespace Bomber::Backend;

RandomAI::RandomAI()
: Sprite()
{
    _state = STATE_NONE;
}

void RandomAI::update(float dt)
{
    Coordinates goalCoords;
    Position delta;
    Position nextPos;

    switch (_state)
    {
        case STATE_NONE:
            goalCoords = AI::getInstance()->getRandomCoordsAround(this->getCoords());
            _goal = Position(goalCoords.x*TILE_WIDTH, goalCoords.y*TILE_HEIGHT);
            _state = STATE_MOVING;
            break;

        case STATE_MOVING:
            delta = _goal - _position;

            if (delta < 2.0f && delta > -0.2f)
            {
                _state = STATE_NONE;
            }
            else
            {
                if (delta.x > 0)
                {
                    nextPos.x = _position.x + 1.0f;
                }
                else
                {
                    nextPos.x = _position.x - 1.0f;
                }

                if (delta.y > 0)
                {
                    nextPos.y = _position.y + 1.0f;
                }
                else
                {
                    nextPos.y = _position.y - 1.0f;
                }
                this->setPosition(nextPos);
            }
            break;
    }
}
