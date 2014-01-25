
#include "AI.h"

using namespace Bomber::Backend;
using namespace Bomber::Common;

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

bool AI::isCoordsCrossable(Coordinates coords)
{
    return this->isCoordsCrossable(coords, false);
}

bool AI::isCoordsCrossable(Coordinates coords, bool ghostMode)
{
    auto obstacles = _state->getObstacleLayer()->getObjectsAtCoords(coords);
    auto bombs = _state->getBombLayer()->getObjectsAtCoords(coords);

    if (obstacles.size() == 0 && bombs.size() == 0)
       return true;

    if (!ghostMode)
        return false;

    for (auto obstacle : obstacles)
    {
        if (!obstacle->getToughness()) 
            return false;
    }

    return true;
}

Coordinates AI::getRandomCoordsAround(Coordinates coords)
{
    return this->getRandomCoordsAround(coords, false);
}

Coordinates AI::getRandomCoordsAround(Coordinates coords, bool ghostMode)
{
    std::vector<Coordinates> candidates;

    for (Coordinates c : coords.getCoordsAround())
    {
        if (this->isCoordsCrossable(c, ghostMode))
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

std::deque<Coordinates> AI::findDirectPath(Coordinates from, Coordinates to)
{
    return this->findDirectPath(from, to, false);
}

std::deque<Coordinates> AI::findDirectPath(Coordinates from, Coordinates to, bool ghostMode)
{
    int dx = abs(to.x - from.x);
    int dy = abs(to.y - from.y);
    int goal;

    int modifierX = 1;
    int modifierY = 1;

    if (to.x < from.x)
    {
        modifierX = -1;
    }
    if (to.y < from.y)
    {
        modifierY = -1;
    }

    float increaceX = 0.0f;
    float increaceY = 0.0f;

    float completenessX = 0.0f;
    float completenessY = 0.0f;

    if (dx == dy)
    {
        increaceX = 1;
        increaceY = 1;
        goal = dx;
    }
    else if (dx == 0.0f)
    {
        increaceY = 1.0f;
        goal = dy;
        completenessX = goal;
    }
    else if (dy == 0.0f)
    {
        increaceX = 1.0f;
        goal = dx;
        completenessY = goal;
    }
    else if (dx > dy)
    {
        increaceX = 1.0f;
        increaceY = dx/dy;
        goal = dx;
    }
    else if (dx < dy)
    {
        increaceX = dy/dx;
        increaceY = 1.0f;
        goal = dy;
    }

    Coordinates current = from;

    std::deque<Coordinates> path;

    while (current != to)
    {
        if (current.y != to.y && completenessX >= completenessY)
        {
            current = Coordinates(current.x, current.y + modifierY);
            completenessY += increaceY;
        }
        else if (current.x != to.x)
        {
            current = Coordinates(current.x + modifierX, current.y);
            completenessX += increaceX;
        }
        else
        {
            if ((from.x < to.x && current.x < to.x) || (from.x > to.x && current.x > to.x))
            {
                current = Coordinates(current.x + modifierX, current.y);
                completenessX += increaceX;
            }
            else if ((from.y < to.y && current.y < to.y) || (from.y > to.y && current.y > to.y))
            {
                current = Coordinates(current.x, current.y + modifierY);
                completenessY += increaceY;
            }
            else
            {
                printf("WTF?????\n");
                printf("diagnostics:\n");
                printf(" - from.x: %d\n", to.x);
                printf(" - from.y: %d\n", to.y);
                printf(" - current.x: %d\n", current.x);
                printf(" - current.y: %d\n", current.y);
                printf(" - to.x: %d\n", to.x);
                printf(" - to.y: %d\n", to.y);
                printf(" - completenessX: %g\n", completenessX);
                printf(" - completenessY: %g\n", completenessY);
                printf(" - increaceX: %g\n", increaceX);
                printf(" - increaceY: %g\n", increaceY);
                printf(" - modifierX: %d\n", modifierX);
                printf(" - modifierY: %d\n", modifierY);
            }
        }

        if (!this->isCoordsCrossable(current, ghostMode))
        {
            if (path.size() == 0)
            {
                path.clear();
                path.push_back(from);
                return path;
            }

            return path;
        }

        path.push_back(current);
    }

    return path;
}

std::deque<Coordinates> AI::findPath(Coordinates from, Coordinates to)
{
    return this->findPath(from, to, false);
}

std::deque<Coordinates> AI::findPath(Coordinates from, Coordinates to, bool ghostMode, bool smart)
{
    if (smart)
        return this->findPath(from, to, ghostMode);
    
    return this->findDirectPath(from, to, ghostMode);
}

std::deque<Coordinates> AI::findPath(Coordinates from, Coordinates to, bool ghostMode)
{
    // TODO: use effective algorithm (A*?) instead of this temporary processor burner!

    std::deque<Coordinates> queue;
    queue.push_back(from);
    //int scoreMap[_state->getWidth()*_state->getHeight()];
    int *scoreMap = (int *) malloc(_state->getWidth()*_state->getHeight()*sizeof(int));
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
            if (!this->isCoordsCrossable(coords, ghostMode))
                continue;

            if (scoreMap[coords.y*_state->getWidth() + coords.x] > currentScore + 1)
            {
                scoreMap[coords.y*_state->getWidth() + coords.x] = currentScore + 1;
                queue.push_back(coords);
            }
        }
    }

    std::deque<Coordinates> path;
    path.push_back(to);
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
    return this->findPathToNearestPlayer(from, range, true, false);
}

std::deque<Coordinates> AI::findPathToNearestPlayer(Coordinates from, float range, bool smart)
{
    return this->findPathToNearestPlayer(from, range, smart, false);
}

std::deque<Coordinates> AI::findPathToNearestPlayer(Coordinates from, float range, bool smart, bool ghostMode)
{
    float smallestDistance = range;
    float distance;

    Sprite *nearestSprite = nullptr;

    for (auto sprite : _state->getSpriteLayer()->getObjects())
    {
        if (sprite->isAI() || sprite->getAttributes()->isDead())
            continue;

        Coordinates spriteCoords = sprite->getCoords();

        if (from == spriteCoords)
        {
            std::deque<Coordinates> path;
            path.push_back(from);
            return path;
        }

        distance = sqrt(pow(from.x - spriteCoords.x, 2) + pow(from.y - spriteCoords.y, 2));

        if (smallestDistance < 0.0 || smallestDistance > distance)
        {
            smallestDistance = distance;
            nearestSprite = sprite;
        }
    }

    if (nearestSprite == nullptr || smallestDistance < 0.0)
        return std::deque<Coordinates>();

    if (!smart)
        return this->findDirectPath(from, nearestSprite->getCoords(), ghostMode);

    return this->findPath(from, nearestSprite->getCoords(), ghostMode);
}

