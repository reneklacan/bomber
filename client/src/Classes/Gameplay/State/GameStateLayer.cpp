
#include "GameStateLayer.h"

GameStateLayer::GameStateLayer(int width, int height)
{
    _width = width;
    _height = height;
    int gridSize = width*height;

    for (int i = 0; i < gridSize; i++)
    {
        std::set<GameObject *> s;
        _grid.push_back(s);
    }
}

void GameStateLayer::addObject(GameObject *object)
{
    object->setEventDelegate(this);
    _objects.insert(object);

    Coordinates nextCoords = object->getNextCoords();
    _grid[nextCoords.y*_width + nextCoords.x].insert(object);
}

void GameStateLayer::removeObject(GameObject *object)
{
    _objects.erase(object);
}

void GameStateLayer::update(GameStateChange *change)
{
    GameObject *object = change->getGameObject();
    Coordinates currentCoords = object->getCoords();
    Coordinates nextCoords = object->getNextCoords();

    if (currentCoords == nextCoords)
        return;

    _grid[currentCoords.y*_width + currentCoords.x].erase(object);
    _grid[nextCoords.y*_width + nextCoords.x].insert(object);
}

void GameStateLayer::getObjectsAroundCoords(Coordinates coords, std::vector<GameObject *> &objects)
{
    for (int y = coords.y - 1; y <= coords.y + 1; y++)
    {
        for (int x = coords.x - 1; x <= coords.x + 1; x++)
        {
            for (GameObject *object : _grid[y*_width + x])
            {
                objects.push_back(object);
            }
        }
    }
}
