
#include "GameStateLayer.h"

using namespace Bomber::Backend;

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
    this->addObject(object->getId(), object);
}

void GameStateLayer::addObject(unsigned int id, GameObject *object)
{
    _objects.at(id) = object;

    Coordinates nextCoords = object->getNextCoords();
    _grid[nextCoords.y*_width + nextCoords.x].insert(object);
}

GameObject *GameStateLayer::getObject(unsigned int id)
{
    return _objects.at(id);
}

void GameStateLayer::removeObject(GameObject *object)
{
    this->removeObject(object->getId());
}

void GameStateLayer::removeObject(unsigned int id)
{
    _objects.erase(_objects.find(id));
}

void GameStateLayer::getObjectsAroundCoords(Coordinates coords, int range, std::vector<GameObject *> &objects)
{
    for (int y = coords.y - range; y <= coords.y + range; y++)
    {
        for (int x = coords.x - range; x <= coords.x + range; x++)
        {
            for (GameObject *object : _grid[y*_width + x])
            {
                objects.push_back(object);
            }
        }
    }
}

void GameStateLayer::getObjectsAroundCoords(Coordinates coords, std::vector<GameObject *> &objects)
{
    this->getObjectsAroundCoords(coords, 1, objects);
}

void GameStateLayer::getObjectsAtCoords(Coordinates coords, std::vector<GameObject *> &objects)
{
    this->getObjectsAroundCoords(coords, 0, objects);
}

