
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
        if (this->isCoordsCrossable(c))
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

bool AI::isCoordsCrossable(Coordinates coords)
{
   if (_state->getObstacleLayer()->getObjectsAtCoords(coords).size() == 0)
       return true;
   return false;
}

std::deque<Coordinates> AI::findPath(Coordinates from, Coordinates to)
{
    // TODO: use effective algorithm (A*?) instead of this temporary processor burner!

    std::deque<Coordinates> queue({from});
    int scoreMap[_state->getWidth()*_state->getHeight()];
    Coordinates current;

    for (unsigned int i = 0; i < _state->getWidth()*_state->getHeight(); i++)
    {
        scoreMap[i] = 999;
    }
    scoreMap[from.y*_state->getWidth() + from.x] = 0;

    int currentScore = 0;

    while (true)
    {
        if (queue.size() == 0)
        {
            return std::deque<Coordinates>();
        }

        current = queue.front();

        if (current == to)
            break;

        queue.pop_front();
        currentScore = scoreMap[current.y*_state->getWidth() + current.x];

        for (auto coords : current.getCoordsAround())
        {
            if (!this->isCoordsCrossable(coords))
                continue;

            if (scoreMap[coords.y*_state->getWidth() + coords.x] > currentScore + 1)
            {
                scoreMap[coords.y*_state->getWidth() + coords.x] = currentScore + 1;
                queue.push_back(coords);
            }
        }
    }

    std::deque<Coordinates> path({to});
    current = to;
    currentScore = scoreMap[to.y*_state->getWidth() + to.x];

    /*
    for (int y = 0; y < _state->getHeight(); y++)
    {
        for (int x = 0; x < _state->getWidth(); x++)
        {
            printf("%d ", scoreMap[y*_state->getWidth() + x]);
        }
        printf("\n");
    }
    */

    while (true)
    {
        for (auto coords : current.getCoordsAround()) 
        {
            if (scoreMap[coords.y*_state->getWidth() + coords.x] == currentScore - 1)
            {
                currentScore--;
                path.push_front(current);

                if (coords == from)
                    return path;

                current = coords;

                break;
            }
        }
    }

    return path;
}

std::deque<Coordinates> AI::findPathToNearestPlayer(Coordinates from, float range)
{
    float smallestDistance = range;
    float distance;

    Sprite *nearestSprite;

    for (auto pair : _state->getSpriteLayer()->getObjects())
    {
        auto sprite = pair.second;

        if (sprite->isAI() || sprite->getAttributes().isDead())
            continue;

        Coordinates spriteCoords = sprite->getCoords();

        if (from == spriteCoords)
            return std::deque<Coordinates>({from});

        distance = sqrt(pow(from.x - spriteCoords.x, 2) + pow(from.y - spriteCoords.y, 2));

        if (smallestDistance < 0.0 || smallestDistance > distance)
        {
            smallestDistance = distance;
            nearestSprite = sprite;
        }
    }

    if (smallestDistance < 0.0)
        return std::deque<Coordinates>();

    return this->findPath(from, nearestSprite->getCoords());
}

