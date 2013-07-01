
#include "AI.h"

using namespace Bomber::Backend;

AI *AI::_instance = nullptr;

AI *AI::getInstance()
{
    if (_instance == nullptr)
    {
        _instance = new AI();
    }
    return _instance;
}

AI::AI()
{

}

void AI::init(GameState *state)
{
    _state = state;
}

void AI::init(GameStateUpdater *gameStateUpdater)
{
    _gameStateUpdater = gameStateUpdater;
}

Coordinates AI::getRandomCoordsAround(Coordinates coords)
{
    std::list<Coordinates> around({
            Coordinates(coords.x, coords.y + 1),
            Coordinates(coords.x, coords.y - 1),
            Coordinates(coords.x - 1, coords.y),
            Coordinates(coords.x + 1, coords.y)
    });
    std::vector<Coordinates> candidates;

    for (Coordinates c : around)
    {
        if (_state->getObstacleLayer()->getObjectsAtCoords(c).size() == 0)
        {
            candidates.push_back(c);
        }
    }

    if (candidates.size() == 0)
    {
        return coords;
    }

    return candidates[std::rand() % candidates.size()];
}
